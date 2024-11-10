#ifndef CCSTD_ARENA_H_
#define CCSTD_ARENA_H_

#include <prelude.h>
#include <stdint.h>

typedef enum {
    AE_NO_ERROR             = 0,
    AE_MALLOC               = 1,
    AE_OVERFLOW             = 2,
    AE_INVALID_ARENA_PASSED = 3,
} ArenaError;
typedef struct Arena Arena;

#ifndef CCS_NOLIBC
Arena* Arena_new(uint64_t size);
void* Arena_alloc(Allocator arena, uint64_t size);
void Arena_clear(Allocator arena);
void Arena_free(Allocator arena);
#endif

ArenaError Arena_error(const Arena* arena);

Arena* Arena_new_alloc(uint64_t size, Allocator allocator, AllocFunc func);
void Arena_free_alloc(Allocator arena, Allocator allocator, FreeFunc func);
void Arena_free_allocation(Allocator allocator, void* ptr);

#endif
