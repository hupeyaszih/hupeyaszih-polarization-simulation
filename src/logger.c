#include "logger.h"
#include <locale.h>
#include <stdio.h>
#include <inttypes.h>


// struct config {
//     uint32_t N; ///< @brief individual count / population size
//
//     uint8_t min_stubbornness;
//     uint8_t max_stubbornness;
//
//     uint8_t min_persuasiveness;
//     uint8_t max_persuasiveness;
//
//     uint32_t initial_average_degree;
//     uint32_t rewire_threshold;
//     uint32_t seed;
// };

void logger_print_config(struct config *config) {
    if(NULL == config) return;

    printf("config = {\n    N: %u,\n    min_stubbornness: %" PRIu8 ",\n    max_stubbornness: %"PRIu8",\n    min_persuasiveness: %"PRIu8",\n    max_persuasiveness: %"PRIu8",\n    initial_average_degree: %u,\n    rewire_threshold: %u,\n    seed: %u\n}\n", config->N, config->min_stubbornness, config->max_stubbornness, config->min_persuasiveness, config->max_persuasiveness, config->initial_average_degree, config->rewire_threshold, config->seed);
}
