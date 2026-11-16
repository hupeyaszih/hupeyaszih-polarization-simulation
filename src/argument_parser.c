#include "argument_parser.h"
#include "globals.h"
#include "hstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_SETTING_COUNT 19
#define SETTING_STR_LEN 48

const char settings[TOTAL_SETTING_COUNT][SETTING_STR_LEN] = {
    "-N",
    "-initial_min_degree",
    "-initial_max_degree",

    "-min_stubbornness",
    "-max_stubbornness",

    "-min_persuasiveness",
    "-max_persuasiveness",

    "-min_openness",
    "-max_openness",

    "-seed",

    "-save_interval",
    "-stats_save_interval",
    "-final_step",
    "-log_dir",

    "-repulsion_constant",
    "-dynamic_reputation_changing_speed",
    "-perceptual_threshold",
    "-threshold_create_edge",
    "-threshold_remove_edge"
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
                uint32_t initial_min_degree = hstring_str_to_uint32(value);
                config->initial_min_degree = initial_min_degree;
                break;
            }case 2: {
                uint32_t initial_max_degree = hstring_str_to_uint32(value);
                config->initial_max_degree = initial_max_degree;
                break;
            }case 3: {
                float min_stubbornness = strtof(value, NULL);
                config->min_stubbornness = globals_convert_float_to_uint8(min_stubbornness);
                break;
            }case 4: {
                float max_stubbornness = strtof(value, NULL);
                config->max_stubbornness = globals_convert_float_to_uint8(max_stubbornness);
                break;
            }case 5: {
                float min_persuasiveness = strtof(value, NULL);
                config->min_persuasiveness = globals_convert_float_to_uint8(min_persuasiveness);
                break;
            }case 6: {
                float max_persuasiveness = strtof(value, NULL);
                config->max_persuasiveness = globals_convert_float_to_uint8(max_persuasiveness);
                break;
            }case 7: {
                float min_openness = strtof(value, NULL);
                config->min_openness = globals_convert_float_to_uint8(min_openness);
                break;
            }case 8: {
                float max_openness = strtof(value, NULL);
                config->max_openness = globals_convert_float_to_uint8(max_openness);
                break;
            }case 9: {
                uint32_t seed = hstring_str_to_uint32(value);
                config->seed = seed;
                break;
            }case 10: {
                uint32_t save_interval = hstring_str_to_uint32(value);
                config->save_interval = save_interval;
                break;
            }case 11: {
                uint32_t stats_save_interval = hstring_str_to_uint32(value);
                config->stats_save_interval = stats_save_interval;
                break;
            }case 12: {
                uint32_t final_step = hstring_str_to_uint32(value);
                config->final_step = final_step;
                break;
            }case 13: {
                config->log_dir = value;
                break;
            }case 14: {
                float repulsion_constant = strtof(value, NULL);
                config->repulsion_constant = globals_convert_float_to_uint32(repulsion_constant);
                break;
            }case 15: {
                uint32_t dynamic_reputation_changing_speed = hstring_str_to_uint32(value);
                config->dynamic_reputation_changing_speed = dynamic_reputation_changing_speed;
                break;
            }case 16: {
                float perceptual_threshold = strtof(value, NULL);
                config->perceptual_threshold = globals_convert_float_to_uint32(perceptual_threshold);
                break;
            }case 17: {
                float threshold_create_edge = strtof(value, NULL);
                config->threshold_create_edge = globals_convert_float_to_uint32(threshold_create_edge);
                break;
            }case 18: {
                float threshold_remove_edge = strtof(value, NULL);
                config->threshold_remove_edge = globals_convert_float_to_uint32(threshold_remove_edge);
                break;
            }
        }
    }
}
