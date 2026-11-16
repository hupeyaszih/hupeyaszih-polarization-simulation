#include "logger.h"
#include "globals.h"
#include "simulation.h"
#include <stdio.h>
#include <inttypes.h>

void logger_print_config(struct config *config) {
    if(NULL == config) return;

    printf("config = {\n    N: %u,\n    min_stubbornness: %f,\n    max_stubbornness: %f,\n    min_persuasiveness: %f,\n    max_persuasiveness: %f,\n    min_openness: %f,\n    max_openness: %f,\n    initial_min_degree: %u,\n    initial_max_degree: %u,\n    seed: %u,\n    repulsion_constant: %f,\n    dynamic_reputation_changing_speed: %d,\n    perceptual_threshold: %f,\n    threshold_create_edge: %f,\n    threshold_remove_edge: %f,\n    save_interval: %d,\n    stats_save_interval: %d,\n    final_step: %lu,\n    log_dir: %s\n}\n", config->N, globals_convert_uint8_to_float(config->min_stubbornness), globals_convert_uint8_to_float(config->max_stubbornness), globals_convert_uint8_to_float(config->min_persuasiveness), globals_convert_uint8_to_float(config->max_persuasiveness), globals_convert_uint8_to_float(config->min_openness), globals_convert_uint8_to_float(config->max_openness), config->initial_min_degree, config->initial_max_degree, config->seed, globals_convert_uint32_to_float(config->repulsion_constant), config->dynamic_reputation_changing_speed, globals_convert_uint32_to_float(config->perceptual_threshold), globals_convert_uint32_to_float(config->threshold_create_edge), globals_convert_uint32_to_float(config->threshold_remove_edge), config->save_interval, config->stats_save_interval, config->final_step, config->log_dir);
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


void logger_clear_old_statistics(const struct simulation *simulation) {
    if(NULL == simulation) return;
    char filename[64];
    snprintf(filename, sizeof(filename), "%s/stats.csv", simulation->config.log_dir);

    FILE *file = fopen(filename, "w");
    if(!file) return;

    fclose(file);
}

void logger_save_statistics(const struct statistics *stats) {
    const struct simulation *simulation = stats->simulation;
    if(NULL == simulation) return;
    char filename[64];
    snprintf(filename, sizeof(filename), "%s/stats.csv", simulation->config.log_dir);

    FILE *check = fopen(filename, "r");
    uint8_t file_exists = NULL != check;
    size_t file_size = 0;
    if(file_exists) {
        fseek(check, 0, SEEK_END);
        file_size = ftell(check);
        fclose(check);
    }
    uint8_t create_new_file = (!file_exists || 0 == file_size);

    FILE *file = NULL;
    if(create_new_file) {
        file = fopen(filename, "w");
        if(!file) {
            return;
        }

        fprintf(file, "step;belief_variance;average_belief;average_dynamic_reputation\n");
    }

    if(!file) {
        file = fopen(filename, "a");
    }
    if(!file) {
        return;
    }

    float f_v = (float)stats->belief_variance / ((double)INT32_MAX * INT32_MAX);
    float f_b = (float)stats->average_belief / (float) (INT32_MAX);
    float f_d = (float)stats->average_dynamic_reputation / (float) UINT32_MAX;

    fprintf(file, "%lu;%f;%f;%f\n", stats->step, f_v, f_b, f_d);
    fclose(file);
}
