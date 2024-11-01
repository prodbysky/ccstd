#ifndef CCSTD_ARENA_H_
#define CCSTD_ARENA_H_

#include "prelude.h"

#include <stdint.h>
typedef struct Arena Arena;

#ifndef CCS_NOLIBC
Arena* Arena_new(uint64_t size);
void* Arena_alloc(Allocator arena, uint64_t size);
void Arena_clear(Allocator arena);
void Arena_free(Allocator arena);
#endif

Arena* Arena_new_alloc(uint64_t size, Allocator allocator, AllocFunc func);
void Arena_free_allocation(Allocator allocator, void* ptr);

void Arena_free_alloc(Allocator arena, Allocator allocator, FreeFunc func);

#endif
