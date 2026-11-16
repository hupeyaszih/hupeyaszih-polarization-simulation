#include "config.h"
#include "globals.h"

struct config config_init_default_config() {
    return (struct config) {
        .N = 1000,
        .initial_min_degree = 6,
        .initial_max_degree = 14,

        .min_stubbornness = 100,
        .max_stubbornness = 140,

        .min_persuasiveness = 100,
        .max_persuasiveness = 140,

        .min_openness = 100,
        .max_openness = 140,

        .repulsion_constant                 = globals_convert_float_to_uint32(0.7f), //0 <= repulsion_constant    <= 1
        .dynamic_reputation_changing_speed  = 20, //0 < dynamic_reputation_changing_speed
        .perceptual_threshold               = globals_convert_float_to_uint32(0.05f),//0 <= perceptual_threshold  <= 1
        .threshold_create_edge              = globals_convert_float_to_uint32(0.5f), //0 <= threshold_create_edge <= 1
        .threshold_remove_edge              = globals_convert_float_to_uint32(0.2f), //0 <= threshold_remove_edge <= 1
        .seed = 13,

        .save_interval = 100,
        .stats_save_interval = 100,
        .final_step    = 1000,
        .log_dir = "./",

        .belief_histogram_bucket_count = 10
    };
}
