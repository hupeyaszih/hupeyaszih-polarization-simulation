#include "logger.h"
#include <stdio.h>
#include <inttypes.h>

void logger_print_config(struct config *config) {
    if(NULL == config) return;

    printf("config = {\n    N: %u,\n    min_stubbornness: %" PRIu8 ",\n    max_stubbornness: %"PRIu8",\n    min_persuasiveness: %"PRIu8",\n    max_persuasiveness: %"PRIu8",\n    min_openness: %"PRIu8",\n    max_openness: %"PRIu8",\n    initial_min_degree: %u,\n    initial_max_degree: %u,\n    rewire_threshold: %u,\n    seed: %u,\n    final_step: %u\n}\n", config->N, config->min_stubbornness, config->max_stubbornness, config->min_persuasiveness, config->max_persuasiveness, config->min_openness, config->max_openness, config->initial_min_degree, config->initial_max_degree, config->rewire_threshold, config->seed, config->final_step);
}
