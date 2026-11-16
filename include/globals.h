#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

static inline uint32_t globals_convert_float_to_uint32(float x) {
    if(x >= 1) return 4294967295;
    else if(x < 0) return 0;
    return (uint32_t)(x * 4294967295.0f);
}

static inline int32_t globals_convert_float_to_int32(float x) {
    if(x >= 1) return INT32_MAX;
    else if(x < -1) return -(INT32_MAX);
    return (int32_t)(x * (float)INT32_MAX);
}

static inline float globals_convert_uint32_to_float(uint32_t x) {
    return (float)(x / 4294967295.0f);
}

static inline float globals_convert_int32_to_float(int32_t x) {
    return (float)x / (float) INT32_MAX;
}


static inline uint8_t globals_convert_float_to_uint8(float x) {
    if(x >= 1) return UINT8_MAX;
    else if(x < 0) return 0;
    return (uint8_t)(x * (float)UINT8_MAX);
}

static inline float globals_convert_uint8_to_float(uint8_t x) {
    return (float)x / (float)UINT8_MAX;
}

#endif
