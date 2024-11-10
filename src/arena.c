#include "../include/arena.h"

#include <stdint.h>

struct Arena {
    char* memory;
    uint64_t used;
    uint64_t capacity;
};

#ifndef CCS_NOLIBC
#include <stdlib.h>
Arena* Arena_new(uint64_t size) {
    Arena* arena = malloc(sizeof(Arena));
    CCS_ASSERT(arena);
    arena->memory = malloc(sizeof(char) * size);
    CCS_ASSERT(arena->memory);
    arena->used     = 0;
    arena->capacity = size;
    return arena;
}
void* Arena_alloc(Allocator arena, uint64_t size) {
    Arena* ar = (Arena*) arena;
    CCS_ASSERT(ar);
    CCS_ASSERT(ar->memory);
    uint64_t alignedSize = (size + 7) & ~7;

    if (ar->used + alignedSize >= ar->capacity) {
        return NULL;
    }
    void* buffer  = &ar->memory[ar->used];
    ar->used     += alignedSize;
    return buffer;
}
void Arena_clear(Allocator arena) {
    Arena* ar = (Arena*) arena;
    CCS_ASSERT(ar);
    CCS_ASSERT(ar->memory);
    ar->used = 0;
}
void Arena_free(Allocator arena) {
    Arena* ar = (Arena*) arena;
    CCS_ASSERT(ar);
    CCS_ASSERT(ar->memory);
    free(ar->memory);
    free(ar);
}
#endif
// Nop since you cant free allocations with an arena
void Arena_free_allocation(Allocator allocator, void* ptr) {
    (void) allocator;
    (void) ptr;
}

Arena* Arena_new_alloc(uint64_t size, Allocator allocator, AllocFunc func) {
    Arena* arena = func(allocator, sizeof(Arena));
    CCS_ASSERT(arena);
    arena->memory = func(allocator, sizeof(char) * size);
    CCS_ASSERT(arena->memory);
    arena->used     = 0;
    arena->capacity = size;
    return arena;
}

void Arena_free_alloc(Allocator arena, Allocator allocator, FreeFunc func) {
    Arena* ar = (Arena*) arena;
    CCS_ASSERT(ar);
    CCS_ASSERT(ar->memory);
    func(allocator, ar->memory);
    func(allocator, ar);
}
