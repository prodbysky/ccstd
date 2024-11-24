#include <dyn_array.h>

#ifndef CCS_NOLIBC
#include <stdlib.h>
DynArray DynArray_new_(uint64_t size) {
    DynArray arr     = {0};
    arr.cap          = 32;
    arr.element_size = size;
    arr.elements     = malloc(size * arr.cap);
    CCS_MEMSET(arr.elements, 0, size * arr.cap);
    return arr;
}
void DynArray_free(DynArray* array) {
    free(array->elements);
    CCS_MEMSET(array, 0, sizeof(DynArray));
}
void DynArray_resize(DynArray* array, uint64_t new_len) {
    if (new_len < array->cap) {
        return;
    }

    array->len      = new_len;
    array->elements = realloc(array->elements, new_len * array->element_size);
}
#endif

DynArray DynArray_new_alloc_(uint64_t size, Allocator a, AllocFunc func) {
    DynArray arr     = {0};
    arr.cap          = 32;
    arr.element_size = size;
    arr.elements     = func(a, size * arr.cap);
    CCS_MEMSET(arr.elements, 0, size * arr.cap);
    return arr;
}

void* DynArray_get_(DynArray* array, uint64_t index) {
    return (void*) ((char*) array->elements + (index * array->element_size));
}

void DynArray_free_alloc(DynArray* array, Allocator a, FreeFunc func) {
    func(a, array->elements);
    CCS_MEMSET(array, 0, sizeof(DynArray));
}

void DynArray_resize_alloc(DynArray* array, uint64_t new_len, Allocator a,
                           ReallocFunc f) {
    if (new_len < array->cap) {
        return;
    }

    array->len      = new_len;
    array->elements = f(a, array->elements, new_len * array->element_size);
}
