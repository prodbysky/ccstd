#ifndef CCSTD_MATH_H_
#define CCSTD_MATH_H_
#include <prelude.h>

#ifndef CCS_PI
#define CCS_PI 3.14159265358979323846
#endif
#ifndef CCS_DEG2RAD
#define CCS_DEG2RAD(deg) (deg) * (CCS_PI / 180)
#endif
#ifndef CCS_RAD2DEG
#define CCS_RAD2DEG(rad) (rad) * (180 / CCS_PI)
#endif

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
} V2u;

V2u V2u_new(uint64_t a, uint64_t b);
V2u V2u_zero();
V2u V2u_one();
V2u V2u_dir(double rads);
V2u V2u_add(V2u v1, V2u v2);
V2u V2u_sub(V2u v1, V2u v2);
V2u V2u_mul(V2u v1, V2u v2);
V2u V2u_div(V2u v1, V2u v2);
V2u V2u_scale(V2u v1, double val);
double V2u_len(V2u v);
double V2u_dot(V2u v1, V2u v2);
double V2u_distance(V2u v1, V2u v2);
double V2u_angle(V2u v1, V2u v2);
V2u V2u_normalize(V2u v);
V2u V2u_lerp(V2u v1, V2u v2, double t);

typedef union {
    struct {
        int64_t x, y;
    };
    struct {
        int64_t u, v;
    };
    struct {
        int64_t i, j;
    };
} V2i;
V2i V2i_new(uint64_t a, uint64_t b);
V2i V2i_zero();
V2i V2i_one();
V2i V2i_dir(double rads);
V2i V2i_add(V2i v1, V2i v2);
V2i V2i_sub(V2i v1, V2i v2);
V2i V2i_mul(V2i v1, V2i v2);
V2i V2i_div(V2i v1, V2i v2);
V2i V2i_scale(V2i v1, double val);
double V2i_len(V2i v);
double V2i_dot(V2i v1, V2i v2);
double V2i_distance(V2i v1, V2i v2);
double V2i_angle(V2i v1, V2i v2);

V2i V2i_negate(V2i v);
V2i V2i_normalize(V2i v);

V2i V2i_lerp(V2i v1, V2i v2, double t);
#endif
