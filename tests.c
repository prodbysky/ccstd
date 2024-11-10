#include "include/arena.h"
#include "include/lcg.h"
#include "include/string.h"

#include <stdint.h>
#include <stdio.h>

int main() {
    Arena* arena = Arena_new(1024);
    String* s    = String_from_cstr_alloc("69420", arena, Arena_alloc);
    printf("%b\n", String_starts_with_cstr(s, "69"));
    printf(STR_FMT "\n", STR_ARG(s));
    String_free_alloc(s, arena, Arena_free_allocation);

    for (int i = 0; i < 10; i++) {
        printf("%d\n", LCG_rand());
    }
}
