#include "hstring.h"
#include <math.h>
#include <string.h>

uint32_t hstring_str_to_uint32(const char *str) {
    size_t len = strlen(str);
    uint32_t num = 0;

    for(uint32_t i = 0; i < len; ++i) {
        char c = str[i];
        uint32_t m = pow(10, len-i-1);
        num += m * (c - 48);
    }

    return num;
}
