#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
struct config {
    uint32_t N; ///< @brief individual count / population size

    uint8_t min_stubbornness;
    uint8_t max_stubbornness;

    uint8_t min_persuasiveness;
    uint8_t max_persuasiveness;

    uint8_t min_openness;
    uint8_t max_openness;

    uint32_t initial_min_degree;
    uint32_t initial_max_degree;

    uint32_t rewire_threshold;
    uint32_t seed;

    uint64_t final_step;

    char *log_dir;
};

struct config config_init_default_config();

#endif
