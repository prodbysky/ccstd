#ifndef CCSTD_DYNARRAY_H_
#define CCSTD_DYNARRAY_H_

#include <prelude.h>
#include <stdint.h>

typedef struct {
    void* elements;
    uint64_t len;
    uint64_t cap;
    uint64_t element_size;
} DynArray;

#define DynArray_new(element_type) DynArray_new_(sizeof(element_type))
#define DynArray_new_alloc(element_type, allocator, func)                      \
    DynArray_new_alloc_(sizeof(element_type), allocator, func)

#define DynArray_get(array_ptr, index, element_type)                           \
    *(element_type*) DynArray_get_((array_ptr), index)
#define DynArray_insert(array_ptr, index, element, element_type)               \
    *((element_type*) ((array_ptr)->elements) + index) = element

#ifndef CCS_NOLIBC
#include <stdlib.h>
DynArray DynArray_new_(uint64_t size);
void DynArray_free(DynArray* array);
void DynArray_resize(DynArray* array, uint64_t new_size);
#define DynArray_push(array, element, element_type)                            \
    do {                                                                       \
        if (array.len >= array.cap) {                                          \
            array.cap *= 1.5;                                                  \
            array.elements =                                                   \
                realloc(array.elements, array.cap * sizeof(element_type));     \
        }                                                                      \
        DynArray_insert(&array, array.len, element, element_type);             \
        array.len++;                                                           \
    } while (0)

#endif

void* DynArray_get_(DynArray* array, uint64_t index);

DynArray DynArray_new_alloc_(uint64_t size, Allocator a, AllocFunc func);
void DynArray_free_alloc(DynArray* array, Allocator a, FreeFunc func);
void DynArray_resize_alloc(DynArray* array, uint64_t new_len, Allocator a,
                           ReallocFunc f);

#endif
