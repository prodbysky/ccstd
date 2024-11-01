#ifndef CCSTD_STRING_H_
#define CCSTD_STRING_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STR_FMT "%.*s"
#define STR_ARG(s)                                                             \
    (int) (String_get_immutable_len((s))), String_get_immutable_str((s))

typedef struct String String;
typedef void* (*AllocFunc)(void* allocator, uint64_t size);
typedef void* (*ReallocFunc)(void* allocator, void* original, uint64_t size);
typedef void (*FreeFunc)(void* allocator, void* ptr);

String* String_new();
String* String_new_with_capacity(uint64_t cap);
String* String_from_cstr(const char* cstr);
const char* String_get_immutable_str(String* str);
uint64_t String_get_immutable_len(String* str);
uint64_t String_get_immutable_cap(String* str);
void String_free(String* str);
char String_pop(String* str);
void String_push_c(String* str, char c);
void String_push_cstr(String* str, const char* cstr);
void String_clear(String* str);
bool String_is_empty(const String* str);
uint64_t String_chop_u64(String* str);
void String_trim_left(String* str);
void String_trim_right(String* str);
void String_trim(String* str);
void String_trim_left_while(String* str, bool (*predicate)(char c));
void String_trim_right_while(String* str, bool (*predicate)(char c));
bool String_starts_with_cstr(const String* str, const char* cstr);

String* String_new_alloc(void* allocator, AllocFunc func);
String* String_new_with_capacity_alloc(uint64_t cap, void* allocator,
                                       AllocFunc func);
void String_free_alloc(String* str, void* allocator, FreeFunc func);
void String_push_c_alloc(String* str, char c, void* allocator,
                         ReallocFunc func);
void String_push_cstr_alloc(String* str, const char* cstr, void* allocator,
                            ReallocFunc func);
#endif // STRING_H_
