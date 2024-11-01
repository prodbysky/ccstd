#ifndef CCSTD_STRING_H_
#define CCSTD_STRING_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STR_FMT "%.*s"
#define STR_ARG(s) (int) ((s).len), ((s).str)

typedef struct {
    char* str;
    uint64_t len;
    uint64_t cap;
} String;

String String_new();
String String_new_with_capacity(uint64_t cap);
String String_from_cstr(const char* c_str);
char String_pop(String* str);
void String_push_c(String* str, char c);
void String_push_cstr(String* str, const char* cstr);
void String_clear(String* str);
bool String_is_empty(String* str);
uint64_t String_chop_u64(String* str);
void String_trim_left(String* str);
void String_trim_right(String* str);

#endif // STRING_H_
