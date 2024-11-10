#include <arena.h>
#include <prelude.h>
#include <stdint.h>

struct Arena {
    char* memory;
    uint64_t used;
    uint64_t capacity;
    ArenaError last_error;
};
static Arena FailedArena = {.last_error = AE_MALLOC};

#ifndef CCS_NOLIBC
#include <stdlib.h>
Arena* Arena_new(uint64_t size) {
    Arena* arena = malloc(sizeof(Arena));
    if (!arena)
        return &FailedArena;
    arena->memory = malloc(sizeof(char) * size);
    if (!arena->memory)
        return &FailedArena;
    arena->used     = 0;
    arena->capacity = size;
    return arena;
}
void* Arena_alloc(Allocator arena, uint64_t size) {
    Arena* ar = (Arena*) arena;

    CCS_ASSERT(ar);
    if (!ar->memory) {
        ar->last_error = AE_INVALID_ARENA_PASSED;
        return NULL;
    }
    uint64_t alignedSize = (size + 7) & ~7;

    if (ar->used + alignedSize >= ar->capacity) {
        ar->last_error = AE_OVERFLOW;
        return NULL;
    }
    void* buffer  = &ar->memory[ar->used];
    ar->used     += alignedSize;
    return buffer;
}
void Arena_clear(Allocator arena) {
    Arena* ar = (Arena*) arena;
    CCS_ASSERT(ar);
    if (!ar->memory) {
        ar->last_error = AE_INVALID_ARENA_PASSED;
        return;
    }
    ar->used = 0;
}
void Arena_free(Allocator arena) {
    if (!arena) {
        return;
    }
    Arena* ar = (Arena*) arena;
    if (!ar->memory) {
        ar->last_error = AE_INVALID_ARENA_PASSED;
        return;
    }
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
    if (!arena)
        return &FailedArena;
    arena->memory = func(allocator, sizeof(char) * size);
    if (!arena->memory)
        return &FailedArena;
    arena->used     = 0;
    arena->capacity = size;
    return arena;
}

void Arena_free_alloc(Allocator arena, Allocator allocator, FreeFunc func) {
    if (!arena) {
        return;
    }
    Arena* ar = (Arena*) arena;
    if (!ar->memory) {
        ar->last_error = AE_INVALID_ARENA_PASSED;
        return;
    }
    func(allocator, ar->memory);
    func(allocator, ar);
}

ArenaError Arena_error(const Arena* arena) { return arena->last_error; }
