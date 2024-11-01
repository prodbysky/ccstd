#include "include/string.h"

#include <stdint.h>
#include <stdio.h>

int main() {
    String s = String_from_cstr("  \t\n  69420!    t");
    String_trim_left(&s);
    uint64_t i = String_chop_u64(&s);
    printf(STR_FMT "\n", STR_ARG(s));
    printf("%lu\n", i);
}
