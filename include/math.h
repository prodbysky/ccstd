#ifndef CCSTD_MATH_H_
#define CCSTD_MATH_H_

#include <stdint.h>
typedef union {
    struct {
        uint64_t x, y;
    };
    struct {
        uint64_t u, v;
    };
    struct {
        uint64_t i, j;
    };
} V2u64;

V2u64 V2u64_new(uint64_t a, uint64_t b);
V2u64 V2u64_zero();
V2u64 V2u64_one();
V2u64 V2u64_add(V2u64 v1, V2u64 v2);
V2u64 V2u64_sub(V2u64 v1, V2u64 v2);
V2u64 V2u64_mul(V2u64 v1, V2u64 v2);
V2u64 V2u64_div(V2u64 v1, V2u64 v2);

#endif
