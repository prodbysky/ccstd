#include <stdint.h>
#include <str.h>

static const uint64_t STRING_INIT_CAP = 32;
static const float STRING_GROW_FACTOR = 1.5;

struct String {
    char* str;
    uint64_t len;
    uint64_t cap;
    StringError last_error;
};
static String FailedString  = {.last_error = SE_MALLOC};
static String FailedString2 = {.last_error = SE_INVALID_CSTRING_PASSED};

#ifndef CCS_NOLIBC
#include <stdlib.h>
String* String_new() { return String_new_with_capacity(STRING_INIT_CAP); }

String* String_new_with_capacity(uint64_t cap) {
    String* str = malloc(sizeof(String));
    if (!str)
        return &FailedString;

    str->str = malloc(sizeof(char) * cap);
    if (!str)
        return &FailedString;
    str->len = 0;
    str->cap = cap;

    memzero(str->str, sizeof(char) * cap);
    return str;
}

String* String_from_cstr(const char* c_str) {
    if (!c_str)
        return &FailedString2;

    const uint64_t len = CCS_STRLEN(c_str);

    String* str = malloc(sizeof(String));
    if (!str)
        return &FailedString;
    str->str = malloc(sizeof(char) * len);
    if (!str->str)
        return &FailedString;
    str->len = len;
    str->cap = len;

    memzero(str->str, sizeof(char) * len);
    CCS_MEMCPY(str->str, c_str, sizeof(char) * len);
    return str;
}

void String_free(String* str) {
    CCS_ASSERT(str);
    if (str->str)
        free(str->str);
    memzero(str, sizeof(String));
    free(str);
}

void String_push_c(String* str, char c) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return;
    }

    if (str->len >= str->cap) {
        str->cap *= STRING_GROW_FACTOR;
        str->str  = realloc(str->str, sizeof(char) * str->cap);
    }
    str->str[str->len++] = c;
}

void String_push_cstr(String* str, const char* cstr) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return;
    }
    if (!cstr) {
        str->last_error = SE_INVALID_CSTRING_PASSED;
        return;
    }
    const uint64_t len = CCS_STRLEN(cstr);
    if (str->len + len >= str->cap) {
        str->cap += len;
        str->str  = realloc(str->str, sizeof(char) * str->cap);
    }
    CCS_MEMCPY(str->str + str->len, cstr, len);
    str->len += len;
}
#endif

const char* String_get_immutable_str(String* str) { return str->str; }
uint64_t String_get_immutable_len(String* str) { return str->len; }
uint64_t String_get_immutable_cap(String* str) { return str->cap; }

char String_pop(String* str) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return 0;
    }
    if (str->len <= 0) {
        str->last_error = SE_STRING_UNDERFLOW;
        return 0;
    }
    char c = str->str[--str->len];
    return c;
}
String* String_from_cstr_alloc(const char* c_str, Allocator allocator,
                               AllocFunc func) {
    if (!c_str) {
        return &FailedString2;
    }
    const uint64_t len = CCS_STRLEN(c_str);

    String* str = func(allocator, sizeof(String));
    if (!str)
        return &FailedString;
    str->str = func(allocator, sizeof(char) * len);
    if (!str->str)
        return &FailedString;
    str->len = len;
    str->cap = len;

    memzero(str->str, sizeof(char) * len);
    CCS_MEMCPY(str->str, c_str, sizeof(char) * len);
    return str;
}

void String_clear(String* str) {
    CCS_ASSERT(str);
    str->len = 0;
}

bool String_is_empty(const String* str) {
    CCS_ASSERT(str);
    return str->len == 0;
}

uint64_t String_chop_u64(String* str) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return 0;
    }
    if (str->len == 0 || str->cap == 0) {
        return 0;
    }

    uint64_t result = 0;
    while (str->len > 0 && CCS_ISDIGIT(*str->str)) {
        result = result * 10 + (*str->str) - '0';
        str->len--;
        str->str++;
    }

    return result;
}

static bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

void String_trim_left(String* str) {
    String_trim_left_while(str, is_whitespace);
}

void String_trim_right(String* str) {
    String_trim_right_while(str, is_whitespace);
}

void String_trim(String* str) {
    String_trim_left(str);
    String_trim_right(str);
}

void String_trim_left_while(String* str, CharPredicate predicate) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return;
    }

    while (predicate(*str->str) && str->len > 0) {
        str->len--;
        str->str++;
    }
}
void String_trim_right_while(String* str, CharPredicate predicate) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return;
    }

    while (predicate(*str->str) && str->len > 0) {
        str->len--;
    }
}

bool String_starts_with_cstr(const String* str, const char* cstr) {
    if (!cstr) {
        return false;
    }
    const uint64_t len = CCS_STRLEN(cstr);

    return CCS_STRNCMP(str->str, cstr, len) == 0;
}

String* String_new_alloc(Allocator allocator, AllocFunc func) {
    return String_new_with_capacity_alloc(STRING_INIT_CAP, allocator, func);
}
String* String_new_with_capacity_alloc(uint64_t cap, Allocator allocator,
                                       AllocFunc func) {

    String* str = func(allocator, sizeof(String));
    if (!str)
        return &FailedString;
    str->str = func(allocator, sizeof(char) * cap);
    if (!str)
        return &FailedString;
    str->len = 0;
    str->cap = cap;
    CCS_ASSERT(str->str);

    memzero(str->str, sizeof(char) * cap);
    return str;
}
void String_free_alloc(String* str, Allocator allocator, FreeFunc func) {
    if (!str)
        return;
    if (str->str)
        func(allocator, str->str);
    func(allocator, str);
}
void String_push_c_alloc(String* str, char c, Allocator allocator,
                         ReallocFunc func) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return;
    }
    if (str->len >= str->cap) {
        str->cap *= STRING_GROW_FACTOR;
        str->str  = func(allocator, str->str, sizeof(char) * str->cap);
    }
    str->str[str->len++] = c;
}
void String_push_cstr_alloc(String* str, const char* cstr, Allocator allocator,
                            ReallocFunc func) {
    CCS_ASSERT(str);
    if (!str->str) {
        str->last_error = SE_INVALID_STRING_PASSED;
        return;
    }
    if (!cstr) {
        str->last_error = SE_INVALID_CSTRING_PASSED;
        return;
    }
    const uint64_t len = CCS_STRLEN(cstr);
    if (str->len + len >= str->cap) {
        str->cap += len;
        str->str  = func(allocator, str->str, sizeof(char) * str->cap);
    }
    CCS_MEMCPY(str->str + str->len, cstr, len);
    str->len += len;
}

StringError String_error(const String* str) { return str->last_error; }
