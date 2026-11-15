#include "logger.h"
#include "globals.h"
#include "simulation.h"
#include <stdio.h>
#include <inttypes.h>

void logger_print_config(struct config *config) {
    if(NULL == config) return;

    printf("config = {\n    N: %u,\n    min_stubbornness: %" PRIu8 ",\n    max_stubbornness: %"PRIu8",\n    min_persuasiveness: %"PRIu8",\n    max_persuasiveness: %"PRIu8",\n    min_openness: %"PRIu8",\n    max_openness: %"PRIu8",\n    initial_min_degree: %u,\n    initial_max_degree: %u,\n    seed: %u,\n    repulsion_constant: %f,\n    dynamic_reputation_changing_speed: %d,\n    perceptual_threshold: %f,\n    threshold_create_edge: %f,\n    threshold_remove_edge: %f,\n    final_step: %lu,\n    log_dir: %s\n}\n", config->N, config->min_stubbornness, config->max_stubbornness, config->min_persuasiveness, config->max_persuasiveness, config->min_openness, config->max_openness, config->initial_min_degree, config->initial_max_degree, config->seed, globals_convert_uint32_to_float(config->repulsion_constant), config->dynamic_reputation_changing_speed, globals_convert_uint32_to_float(config->perceptual_threshold), globals_convert_uint32_to_float(config->threshold_create_edge), globals_convert_uint32_to_float(config->threshold_remove_edge),config->final_step, config->log_dir);
}

void logger_save_edges(const struct simulation *simulation) {
    if(NULL == simulation) return;
    char filename[64];
    snprintf(filename, sizeof(filename), "%s/edges_%"PRIu64".csv", simulation->config.log_dir, simulation->step);

    FILE *file = fopen(filename, "w");

    if(NULL == file) return;

    fprintf(file, "src_id;destination_id\n");

    for(uint32_t i = 0;i < simulation->config.N; ++i) {
        const struct node *node = simulation->nodes + i;
        for(uint32_t k = 0;k < node->edge_count; ++k) {
            const struct edge *edge = node->edges + k;
            fprintf(file, "%u;%u\n", edge->source_id, edge->destination_id);
        }
    }

    fclose(file);
}

void logger_save_nodes(const struct simulation *simulation) {
    if(NULL == simulation) return;
    char filename[64];
    snprintf(filename, sizeof(filename), "%s/nodes_%"PRIu64".csv", simulation->config.log_dir, simulation->step);

    FILE *file = fopen(filename, "w");

    if(NULL == file) return;

    fprintf(file, "id;belief;persuasiveness;stubbornness;openness;dynamic_reputation;edge_count\n");

    for(uint32_t i = 0;i < simulation->config.N; ++i) {
        const struct node *node = simulation->nodes + i;
        fprintf(file, "%u;%f;%u;%u;%u;%u;%u\n", node->id, globals_convert_int32_to_float(node->belief), node->persuasiveness, node->stubbornness, node->openness, node->dynamic_reputation, node->edge_count);
    }

    fclose(file);
}
