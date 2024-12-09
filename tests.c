#include "dyn_array.h"

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

int arena_tests();
int string_tests();

int main() {
    if (arena_tests() != 0)
        return 1;
    if (string_tests() != 0)
        return 1;
    DynArray arr = DynArray_new(int);
    for (int i = 0; i < 10; i++) {
        DynArray_push(arr, i, int);
    }

    for (int i = 0; i < 10; i++) {
        printf("%d\n", DynArray_get(&arr, i, int));
    }

    // TODO: Math tests when I realize how to reasonably test it
    return 0;
}

int arena_tests() {
    printf(ANSI_GREEN "Arena\n" ANSI_RESET);

    Arena* arena = Arena_new(1024);
    uint64_t len = _get_arena_capacity(arena);
    if (len != 1024) {
        printf(ANSI_RED "\tExpected capacity: %d, got: %zu\n" ANSI_RESET, 1024,
               len);
        printf(ANSI_RED "\tArena: " ANSI_RESET "test `Arena_new` failed!\n");
        return 1;
    }
    printf(ANSI_GREEN "\tArena: " ANSI_RESET "`Arena_new` success\n");
    Arena_free(arena);

    arena           = Arena_new(1024);
    int* allocation = Arena_alloc(arena, sizeof(int));
    (void) allocation;
    uint64_t used = _get_arena_used(arena);
    if (used != 8) {
        printf(ANSI_RED "\tExpected used amount: %d, got: %zu\n" ANSI_RESET, 8,
               used);
        printf(ANSI_RED "\tArena: " ANSI_RESET "test `Arena_alloc` failed!\n");
        return 1;
    }
    printf(ANSI_GREEN "\tArena: " ANSI_RESET "`Arena_alloc` success\n");
    Arena_free(arena);

    arena      = Arena_new(1024);
    allocation = Arena_alloc(arena, sizeof(int));
    Arena_clear(arena);
    used = _get_arena_used(arena);
    if (used != 0) {
        printf(ANSI_RED "\tExpected used amount: %d, got: %zu\n" ANSI_RESET, 0,
               used);
        printf(ANSI_RED "\tArena: " ANSI_RESET "test `Arena_clear` failed!\n");
        return 1;
    }
    printf(ANSI_GREEN "\tArena: " ANSI_RESET "`Arena_clear` success\n");
    Arena_free(arena);
    printf(ANSI_GREEN "Arena: " ANSI_RESET "tests finished with no fails!\n");
    return 0;
}

int string_tests() {
    printf(ANSI_GREEN "String\n" ANSI_RESET);
    String* str  = String_new();
    uint64_t cap = String_get_immutable_cap(str);
    if (cap != 32) {
        printf(ANSI_RED "\tExpected capacity: %d, got: %zu\n" ANSI_RESET, 32,
               cap);
        printf(ANSI_RED "\tString: " ANSI_RESET "test `String_new` failed!\n");
        return 1;
    }
    String_free(str);
    printf(ANSI_GREEN "\tString: " ANSI_RESET "`String_new` success\n");

    const char* test_cstr = "Hello!";
    str                   = String_from_cstr(test_cstr);
    cap                   = String_get_immutable_cap(str);
    uint64_t len          = String_get_immutable_cap(str);

    if (cap != strlen(test_cstr)) {
        printf(ANSI_RED "\tExpected capacity: %zu, got: %zu\n" ANSI_RESET,
               strlen(test_cstr), cap);
        printf(ANSI_RED "\tString: " ANSI_RESET
                        "test `String_from_cstr` failed!\n");
        return 1;
    }
    String_free(str);
    printf(ANSI_GREEN "\tString: " ANSI_RESET "`String_from_cstr` success\n");

    str = String_new_with_capacity(1);
    String_push_c(str, 'c');
    len = String_get_immutable_cap(str);

    if (len != 1) {
        printf(ANSI_RED "\tExpected length: %d, got: %zu\n" ANSI_RESET, 1, len);
        printf(ANSI_RED "\tString: " ANSI_RESET
                        "test `String_from_pushc` failed!\n");
        return 1;
    }
    String_free(str);
    printf(ANSI_GREEN "\tString: " ANSI_RESET "`String_push_c` success\n");

    str = String_new_with_capacity(10);
    String_push_cstr(str, test_cstr);
    len = String_get_immutable_cap(str);

    if (len != 10) {
        printf(ANSI_RED "\tExpected length: %d, got: %zu\n" ANSI_RESET, 10,
               len);
        printf(ANSI_RED "\tString: " ANSI_RESET
                        "test `String_from_push_cstr` failed!\n");
        return 1;
    }
    String_free(str);
    printf(ANSI_GREEN "\tString: " ANSI_RESET "`String_push_c_str` success\n");

    printf(ANSI_GREEN "String: " ANSI_RESET "tests finished with no fails!\n");
    return 0;
}
