#ifndef CCSTD_PRELUDE_H_
#define CCSTD_PRELUDE_H_
#include <stdbool.h>
#include <stdint.h>

#define memzero(ptr, n) CCS_MEMSET((ptr), 0, n)
typedef void* Allocator;
typedef void* (*AllocFunc)(Allocator allocator, uint64_t size);
typedef void* (*ReallocFunc)(Allocator allocator, void* original,
                             uint64_t size);
typedef void (*FreeFunc)(Allocator allocator, void* ptr);
typedef bool (*CharPredicate)(char c);

#ifndef CCS_ASSERT
#ifdef CCS_NOLIBC
#error No assert function provided!
#else
#include <assert.h>
#define CCS_ASSERT(cond) assert((cond))
#endif
#endif

#ifndef CCS_MEMSET
#ifdef CCS_NOLIBC
#error No memset function provided!
#else
#include <string.h>
#define CCS_MEMSET(ptr, c, n) memset((ptr), (c), (n))
#endif
#endif

#ifndef CCS_MEMCPY
#ifdef CCS_NOLIBC
#error No memcpy function provided!
#else
#include <string.h>
#define CCS_MEMCPY(dest, src, n) memcpy((dest), (src), (n))
#endif
#endif

#ifndef CCS_STRLEN
#ifdef CCS_NOLIBC
#error No strlen function provided!
#else
#include <string.h>
#define CCS_STRLEN(ptr) strlen(ptr)
#endif
#endif

#ifndef CCS_STRNCMP
#ifdef CCS_NOLIBC
#error No strncmp function provided!
#else
#include <string.h>
#define CCS_STRNCMP(s1, s2, n) strncmp((s1), (s2), (n))
#endif
#endif

#ifndef CCS_ISDIGIT
#ifdef CCS_NOLIBC
#error No isdigit function provided!
#else
#include <ctype.h>
#define CCS_ISDIGIT(c) isdigit((c))
#endif
#endif

#ifndef CCS_COS
#ifdef CCS_NOLIBC
#error No cos function provided!
#else
#include <math.h>
#define CCS_COS(rads) cos(rads)
#endif
#endif

#ifndef CCS_SIN
#ifdef CCS_NOLIBC
#error No sin function provided!
#else
#include <math.h>
#define CCS_SIN(rads) sin(rads)
#endif
#endif

#ifndef CCS_SQRT
#ifdef CCS_NOLIBC
#error No sqrt function provided!
#else
#include <math.h>
#define CCS_SQRT(x) sqrt(x)
#endif
#endif

#ifndef CCS_ATAN2F
#ifdef CCS_NOLIBC
#error No atan2f function provided!
#else
#include <math.h>
#define CCS_ATAN2F(x, y) atan2f(x, y)
#endif
#endif

#endif
