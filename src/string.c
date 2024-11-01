#include "../include/string.h"

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define memzero(ptr, n) memset((ptr), 0, n)
const static uint64_t STRING_INIT_CAP = 32;
const static float STRING_GROW_FACTOR = 1.5;

String String_new() { return String_new_with_capacity(STRING_INIT_CAP); }

String String_new_with_capacity(uint64_t cap) {
    String str = {
        .str = (char*) malloc(sizeof(char) * cap),
        .len = 0,
        .cap = cap,
    };

    if (!str.str)
        return str;

    memzero(str.str, sizeof(char) * cap);
    return str;
}

String String_from_cstr(const char* c_str) {
    assert(c_str);
    const uint64_t len = strlen(c_str);

    String str = {
        .str = (char*) malloc(sizeof(char) * len),
        .len = len,
        .cap = len,
    };

    if (!str.str)
        return str;

    memzero(str.str, sizeof(char) * len);
    memcpy(str.str, c_str, sizeof(char) * len);
    return str;
}

char String_pop(String* str) {
    assert(str);
    assert(str->len > 0);
    assert(str->str);
    char c = str->str[--str->len];
    return c;
}

void String_push_c(String* str, char c) {
    assert(str);
    assert(str->str);
    if (str->len >= str->cap) {
        str->cap *= STRING_GROW_FACTOR;
        str->str  = realloc(str->str, sizeof(char) * str->cap);
    }
    str->str[str->len++] = c;
}

void String_push_cstr(String* str, const char* cstr) {
    assert(str);
    assert(str->str);
    assert(cstr);
    const uint64_t len = strlen(cstr);
    if (str->len + len >= str->cap) {
        str->cap += len;
        str->str  = realloc(str->str, sizeof(char) * str->cap);
    }
    memcpy(str->str + str->len, cstr, len);
    str->len += len;
}

void String_clear(String* str) {
    assert(str);
    assert(str->str);
    str->len = 0;
}

bool String_is_empty(String* str) {
    assert(str);
    assert(str->str);
    return str->len == 0;
}

uint64_t String_chop_u64(String* str) {
    assert(str);
    assert(str->str);
    if (str->len == 0 || str->cap == 0) {
        return 0;
    }

    uint64_t result = 0;
    while (str->len > 0 && isdigit(*str->str)) {
        result = result * 10 + (*str->str) - '0';
        str->len--;
        str->str++;
    }

    return result;
}

void String_trim_left(String* str) {
    assert(str);
    assert(str->str);

    while ((*str->str == ' ' || *str->str == '\t' || *str->str == '\n') &&
           str->len > 0) {
        str->len--;
        str->str++;
    }
}

void String_trim_right(String* str) {
    assert(str);
    assert(str->str);

    while ((*(str->str + str->len - 1) == ' ' ||
            *(str->str + str->len - 1) == '\t' ||
            *(str->str + str->len - 1) == '\n') &&
           str->len > 0) {
        str->len--;
    }
}
