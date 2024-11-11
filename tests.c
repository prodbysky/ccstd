#include <arena.h>
#include <lcg.h>
#include <stdint.h>
#include <stdio.h>
#include <str.h>

#define ANSI_GREEN "\x1b[32m"
#define ANSI_RED "\x1b[31m"
#define ANSI_RESET "\x1b[0m"

uint64_t _get_arena_capacity(Arena* arena) {
    return *(((uint64_t*) arena) + 2);
}
uint64_t _get_arena_used(Arena* arena) { return *(((uint64_t*) arena) + 1); }

int main() {
    // Arena tests
    printf(ANSI_GREEN "Arena " ANSI_RESET "Tests\n");

    Arena* arena = Arena_new(1024);
    uint64_t len = _get_arena_capacity(arena);
    if (len != 1024) {
        printf(ANSI_RED "Expected capacity: %d, got: %zu\n" ANSI_RESET, 1024,
               len);
        printf(ANSI_RED "Arena: " ANSI_RESET "test `Arena_new` failed!\n");
        return 1;
    }
    printf(ANSI_GREEN "Arena: " ANSI_RESET "`Arena_new` success\n");
    Arena_free(arena);

    arena           = Arena_new(1024);
    int* allocation = Arena_alloc(arena, sizeof(int));
    uint64_t used   = _get_arena_used(arena);
    if (used != 8) {
        printf(ANSI_RED "Expected used amount: %d, got: %zu\n" ANSI_RESET, 8,
               used);
        printf(ANSI_RED "Arena: " ANSI_RESET "test `Arena_alloc` failed!\n");
        return 1;
    }
    printf(ANSI_GREEN "Arena: " ANSI_RESET "`Arena_alloc` success\n");
    Arena_free(arena);

    arena      = Arena_new(1024);
    allocation = Arena_alloc(arena, sizeof(int));
    Arena_clear(arena);
    used = _get_arena_used(arena);
    if (used != 0) {
        printf(ANSI_RED "Expected used amount: %d, got: %zu\n" ANSI_RESET, 0,
               used);
        printf(ANSI_RED "Arena: " ANSI_RESET "test `Arena_clear` failed!\n");
        return 1;
    }
    printf(ANSI_GREEN "Arena: " ANSI_RESET "`Arena_clear` success\n");
    Arena_free(arena);
    printf(ANSI_GREEN "Arena: " ANSI_RESET "tests finished with no fails!\n");
}
