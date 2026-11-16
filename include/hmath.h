#ifndef HMATH_H
#define HMATH_H

#include <stdint.h>

#define H_U8_TO_U32(x) ((uint32_t)x * 0x01010101)

static inline uint32_t hclamp_u32(uint32_t value, uint32_t min, uint32_t max) {
    if(value > max) return max;
    else if(value < min) return min;
    return value;
}

static inline int32_t hclamp_i32(int32_t value, int32_t min, int32_t max) {
    if(value > max) return max;
    else if(value < min) return min;
    return value;
}


static inline uint64_t hclamp_u64(uint64_t value, uint64_t min, uint64_t max) {
    if(value > max) return max;
    else if(value < min) return min;
    return value;
}

static inline int64_t hclamp_i64(int64_t value, int64_t min, int64_t max) {
    if(value > max) return max;
    else if(value < min) return min;
    return value;
}

#endif
