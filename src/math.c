#include "../include/math.h"

#include "../include/prelude.h"

V2u V2u_new(uint64_t a, uint64_t b) { return (V2u) {.x = a, .y = b}; }
V2u V2u_zero() { return (V2u) {.x = 0, .y = 0}; }
V2u V2u_one() { return (V2u) {.x = 1, .y = 1}; }

V2u V2u_dir(double rads) {
    return (V2u) {
        .x = CCS_COS(rads),
        .y = CCS_SIN(rads),
    };
}
V2u V2u_add(V2u v1, V2u v2) {
    return (V2u) {.x = v1.x + v2.x, .y = v1.y + v2.y};
}
V2u V2u_sub(V2u v1, V2u v2) {
    return (V2u) {.x = v1.x - v2.x, .y = v1.y - v2.y};
}
V2u V2u_mul(V2u v1, V2u v2) {
    return (V2u) {.x = v1.x * v2.x, .y = v1.y * v2.y};
}
V2u V2u_div(V2u v1, V2u v2) {
    return (V2u) {.x = v1.x / v2.x, .y = v1.y / v2.y};
}

V2u V2u_scale(V2u v1, double val) {
    return V2u_mul(v1, (V2u) {.x = val, .y = val});
}
double V2u_len(V2u v) { return CCS_SQRT(v.x * v.x + v.y * v.y); }
double V2u_dot(V2u v1, V2u v2) { return v1.x * v2.x + v1.y * v2.y; }
double V2u_distance(V2u v1, V2u v2) {
    return CCS_SQRT((v1.x - v2.x) * (v1.x - v2.x) +
                    (v1.y - v2.y) * (v1.y - v2.y));
}

double V2u_angle(V2u v1, V2u v2) {
    float dot = v1.x * v2.x + v1.y * v2.y;
    float det = v1.x * v2.y - v1.y * v2.x;
    return CCS_ATAN2F(det, dot);
}

V2u V2u_normalize(V2u v) {
    V2u result    = {0};
    double length = CCS_SQRT((v.x * v.x) + (v.y * v.y));

    if (length > 0) {
        double inverse_length = 1.0f / length;
        result.x              = v.x * inverse_length;
        result.y              = v.y * inverse_length;
    }

    return result;
}

V2u V2u_lerp(V2u v1, V2u v2, double t) {
    return (V2u) {
        .x = v1.x + t * (v2.x - v1.x),
        .y = v1.y + t * (v2.y - v1.y),
    };
}

V2i V2i_new(uint64_t a, uint64_t b) { return (V2i) {.x = a, .y = b}; }
V2i V2i_zero() { return (V2i) {.x = 0, .y = 0}; }
V2i V2i_one() { return (V2i) {.x = 1, .y = 1}; }
V2i V2i_dir(double rads) {
    return (V2i) {
        .x = CCS_COS(rads),
        .y = CCS_SIN(rads),
    };
}

V2i V2i_add(V2i v1, V2i v2) {
    return (V2i) {.x = v1.x + v2.x, .y = v1.y + v2.y};
}
V2i V2i_sub(V2i v1, V2i v2) {
    return (V2i) {.x = v1.x - v2.x, .y = v1.y - v2.y};
}
V2i V2i_mul(V2i v1, V2i v2) {
    return (V2i) {.x = v1.x * v2.x, .y = v1.y * v2.y};
}
V2i V2i_div(V2i v1, V2i v2) {
    return (V2i) {.x = v1.x / v2.x, .y = v1.y / v2.y};
}
V2i V2i_scale(V2i v1, double val) {
    return V2i_mul(v1, (V2i) {.x = val, .y = val});
}

double V2i_len(V2i v) { return CCS_SQRT(v.x * v.x + v.y * v.y); }

double V2i_dot(V2i v1, V2i v2) { return v1.x * v2.x + v1.y * v2.y; }

double V2i_distance(V2i v1, V2i v2) {
    return CCS_SQRT((v1.x - v2.x) * (v1.x - v2.x) +
                    (v1.y - v2.y) * (v1.y - v2.y));
}

double V2i_angle(V2i v1, V2i v2) {
    float dot = v1.x * v2.x + v1.y * v2.y;
    float det = v1.x * v2.y - v1.y * v2.x;
    return CCS_ATAN2F(det, dot);
}

V2i V2i_negate(V2i v) {
    return (V2i) {
        .x = -v.x,
        .y = -v.y,
    };
}

V2i V2i_normalize(V2i v) {
    V2i result    = {0};
    double length = CCS_SQRT((v.x * v.x) + (v.y * v.y));

    if (length > 0) {
        double inverse_length = 1.0f / length;
        result.x              = v.x * inverse_length;
        result.y              = v.y * inverse_length;
    }

    return result;
}
V2i V2i_lerp(V2i v1, V2i v2, double t) {
    return (V2i) {
        .x = v1.x + t * (v2.x - v1.x),
        .y = v1.y + t * (v2.y - v1.y),
    };
}
