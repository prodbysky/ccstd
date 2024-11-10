#include "../include/math.h"

V2u64 V2u64_new(uint64_t a, uint64_t b) { return (V2u64) {.x = a, .y = b}; }
V2u64 V2u64_zero() { return (V2u64) {0, 0}; }
V2u64 V2u64_one() { return (V2u64) {1, 1}; }
