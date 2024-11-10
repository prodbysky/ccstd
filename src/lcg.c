#include "../include/lcg.h"

#include <stdint.h>
static uint32_t seed    = 1;
static const uint32_t A = 1902514395;
static const uint32_t C = 48392;
static const uint32_t M = 2147483648;

void LCG_new_seed(uint32_t new_seed) { seed = new_seed; }
uint32_t LCG_rand() {
    seed = (A * seed + C) % M;
    return seed;
}
