#ifndef CCSTD_STRING_H_
#define CCSTD_STRING_H_

#include "prelude.h"

#include <stdbool.h>
#include <stdint.h>

#define STR_FMT "%.*s"
#define STR_ARG(s)                                                             \
    (int) (String_get_immutable_len((s))), String_get_immutable_str((s))

typedef struct String String;

#ifndef CCS_NOLIBC
String* String_new();
String* String_new_with_capacity(uint64_t cap);
String* String_from_cstr(const char* cstr);
void String_free(String* str);
void String_push_c(String* str, char c);
void String_push_cstr(String* str, const char* cstr);
#endif

const char* String_get_immutable_str(String* str);
uint64_t String_get_immutable_len(String* str);
uint64_t String_get_immutable_cap(String* str);

char String_pop(String* str);
void String_clear(String* str);

bool String_is_empty(const String* str);

uint64_t String_chop_u64(String* str);

void String_trim_left(String* str);
void String_trim_right(String* str);
void String_trim(String* str);
void String_trim_left_while(String* str, CharPredicate predicate);
void String_trim_right_while(String* str, CharPredicate predicate);

bool String_starts_with_cstr(const String* str, const char* cstr);

String* String_from_cstr_alloc(const char* c_str, Allocator allocator,
                               AllocFunc func);
String* String_new_alloc(Allocator allocator, AllocFunc func);

String* String_new_with_capacity_alloc(uint64_t cap, Allocator allocator,
                                       AllocFunc func);
void String_free_alloc(String* str, void* allocator, FreeFunc func);
void String_push_c_alloc(String* str, char c, Allocator allocator,
                         ReallocFunc func);
void String_push_cstr_alloc(String* str, const char* cstr, Allocator allocator,
                            ReallocFunc func);

#endif // STRING_H_
