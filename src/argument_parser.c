#include "argument_parser.h"
#include "hstring.h"
#include <string.h>

#define TOTAL_SETTING_COUNT 8
#define SETTING_STR_LEN 24

const char settings[TOTAL_SETTING_COUNT][SETTING_STR_LEN] = {
    "-N",
    "-initial_average_degree",

    "-min_stubbornness",
    "-max_stubbornness",

    "-min_persuasiveness",
    "-max_persuasiveness",

    "-rewire_threshold",
    "-seed"
};

uint32_t get_setting_id(char *str) {
    for(uint32_t i = 0;i < TOTAL_SETTING_COUNT; ++i) {
        size_t str_len = strlen(str);
        size_t max_len = SETTING_STR_LEN;

        str_len = str_len > max_len ? max_len : str_len;

        if(0 == strncmp(str, settings[i], str_len)) return i;
    }
    return -1;
}

void argument_parser_parse_config(struct config *const config, int argc, char *argv[]) {
    for(uint32_t i = 0;i < argc; ++i) {
        uint32_t setting_id = get_setting_id(argv[i]);
        if(setting_id == -1) continue;
        char *arg = argv[i];
        if(i >= argc+1) break;
        ++i;
        char *value = argv[i];

        switch (setting_id) {
            case 0: {
                uint32_t N = hstring_str_to_uint32(value);
                config->N = N;
                break;
            }case 1: {
                uint32_t initial_avg_degree = hstring_str_to_uint32(value);
                config->initial_average_degree = initial_avg_degree;
                break;
            }case 2: {
                uint32_t min_stubbornness = hstring_str_to_uint32(value);
                config->min_stubbornness = min_stubbornness;
                break;
            }case 3: {
                uint32_t max_stubbornness = hstring_str_to_uint32(value);
                config->max_stubbornness = max_stubbornness;
                break;
            }case 4: {
                uint32_t min_persuasiveness = hstring_str_to_uint32(value);
                config->min_persuasiveness = min_persuasiveness;
                break;
            }case 5: {
                uint32_t max_persuasiveness = hstring_str_to_uint32(value);
                config->max_persuasiveness = max_persuasiveness;
                break;
            }case 6: {
                uint32_t rewire_threshold = hstring_str_to_uint32(value);
                config->rewire_threshold = rewire_threshold;
                break;
            }case 7: {
                uint32_t seed = hstring_str_to_uint32(value);
                config->seed = seed;
                break;
            }
        }
    }
}
