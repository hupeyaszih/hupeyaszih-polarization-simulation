#include "config.h"
#include "globals.h"

struct config config_init_default_config() {
    return (struct config) {
        .N = 1000,
        .initial_average_degree = 10,

        .min_stubbornness = 100,
        .max_stubbornness = 140,

        .min_persuasiveness = 100,
        .max_persuasiveness = 140,

        .rewire_threshold = globals_convert_float_to_uint32(0.2f),
        .seed = 13
    };
}
