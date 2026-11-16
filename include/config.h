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

    uint32_t seed;

    uint32_t repulsion_constant;
    uint32_t dynamic_reputation_changing_speed;
    uint32_t perceptual_threshold;
    uint32_t threshold_create_edge;
    uint32_t threshold_remove_edge;

    uint32_t save_interval;
    uint32_t stats_save_interval;
    uint32_t belief_histogram_bucket_count;
    uint64_t final_step;

    char *log_dir;
};

struct config config_init_default_config();

#endif
