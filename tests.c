#include "include/string.h"

#include <stdint.h>
#include <stdio.h>

int main() {
    String* s = String_from_cstr("69420");
    printf("%b\n", String_starts_with_cstr(s, "69"));
    printf(STR_FMT "\n", STR_ARG(s));
    String_free(s);
}
