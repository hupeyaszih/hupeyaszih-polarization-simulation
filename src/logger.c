#include "logger.h"
#include "globals.h"
#include "simulation.h"
#include <stdio.h>
#include <inttypes.h>

void logger_print_config(struct config *config) {
    if(NULL == config) return;

    printf("config = {\n    N: %u,\n    min_stubbornness: %" PRIu8 ",\n    max_stubbornness: %"PRIu8",\n    min_persuasiveness: %"PRIu8",\n    max_persuasiveness: %"PRIu8",\n    min_openness: %"PRIu8",\n    max_openness: %"PRIu8",\n    initial_min_degree: %u,\n    initial_max_degree: %u,\n    rewire_threshold: %u,\n    seed: %u,\n    final_step: %u\n}\n", config->N, config->min_stubbornness, config->max_stubbornness, config->min_persuasiveness, config->max_persuasiveness, config->min_openness, config->max_openness, config->initial_min_degree, config->initial_max_degree, config->rewire_threshold, config->seed, config->final_step);
}

void logger_save_edges(const struct simulation *simulation) {
    if(NULL == simulation) return;
    char filename[64];
    snprintf(filename, sizeof(filename), "edges_%"PRIu64".csv", simulation->step);

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
    snprintf(filename, sizeof(filename), "nodes_%"PRIu64".csv", simulation->step);

    FILE *file = fopen(filename, "w");

    if(NULL == file) return;

    fprintf(file, "id;belief;persuasiveness;stubbornness;openness;dynamic_reputation;edge_count\n");

    for(uint32_t i = 0;i < simulation->config.N; ++i) {
        const struct node *node = simulation->nodes + i;
        fprintf(file, "%u;%f;%u;%u;%u;%u;%u\n", node->id, globals_convert_uint32_to_float(node->belief), node->persuasiveness, node->stubbornness, node->openness, node->dynamic_reputation, node->edge_count);
    }

    fclose(file);
}
