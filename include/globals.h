#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

static inline uint32_t globals_convert_float_to_uint32(float x) {
    if(x >= 1) return 4294967295;
    else if(x < 0) return 0;
    return (uint32_t)(x * 4294967295.0f);
}

static inline float globals_convert_uint32_to_float(float x) {
    return (float)(x / 4294967295.0f);
}

#endif
