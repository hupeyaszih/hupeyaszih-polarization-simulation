#include "logger.h"
#include "globals.h"
#include "hmath.h"
#include "simulation.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

void logger_print_config(struct config *config) {
    if(NULL == config) return;

    printf("config = {\n    N: %u,\n    min_stubbornness: %f,\n    max_stubbornness: %f,\n    min_persuasiveness: %f,\n    max_persuasiveness: %f,\n    min_openness: %f,\n    max_openness: %f,\n    initial_min_degree: %u,\n    initial_max_degree: %u,\n    seed: %u,\n    repulsion_constant: %f,\n    reputation_inertia: %d,\n    perceptual_threshold: %f,\n    threshold_create_edge: %f,\n    threshold_remove_edge: %f,\n    save_interval: %d,\n    stats_save_interval: %d,\n    final_step: %lu,\n    log_dir: %s,\n    belief_histogram_bucket_count: %u\n}\n", config->N, globals_convert_uint8_to_float(config->min_stubbornness), globals_convert_uint8_to_float(config->max_stubbornness), globals_convert_uint8_to_float(config->min_persuasiveness), globals_convert_uint8_to_float(config->max_persuasiveness), globals_convert_uint8_to_float(config->min_openness), globals_convert_uint8_to_float(config->max_openness), config->initial_min_degree, config->initial_max_degree, config->seed, globals_convert_uint32_to_float(config->repulsion_constant), config->reputation_inertia, globals_convert_uint32_to_float(config->perceptual_threshold), globals_convert_uint32_to_float(config->threshold_create_edge), globals_convert_uint32_to_float(config->threshold_remove_edge), config->save_interval, config->stats_save_interval, config->final_step, config->log_dir, config->belief_histogram_bucket_count);
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
    float f_d = (float)stats->average_dynamic_reputation / (float) UINT8_MAX;

    fprintf(file, "%lu;%f;%f;%f\n", stats->step, f_v, f_b, f_d);
    fclose(file);
}


void logger_print_belief_histogram(const struct simulation *simulation) {
    if(NULL == simulation) return;

    const struct node *nodes = simulation->nodes;
    const uint32_t N = simulation->config.N;
    const uint32_t bucket_count = simulation->config.belief_histogram_bucket_count;

    uint32_t *buckets = calloc(bucket_count, sizeof(uint32_t));
    for(uint32_t i = 0;i < N; ++i) {
        const struct node *node = nodes + i;
        const int64_t normalized_belief = (int64_t)node->belief + INT32_MAX;

        uint32_t idx = (uint32_t)((int64_t)normalized_belief * bucket_count / (2 * (int64_t)INT32_MAX));
        idx = hclamp_u32(idx, 0, bucket_count-1);

        ++buckets[idx];
    }

    printf("\n\n==Belief Histogram==\n\n");
    for(uint32_t i = 0; i < bucket_count; ++i) {
        double range_start = -1.0 + (i * 2.0 / bucket_count);
        double range_end   = -1.0 + ((i+1) * 2.0 / bucket_count);

        uint32_t bar_length = (uint64_t) buckets[i] * 40 / N;

        printf("[%+0.2f, %+0.2f]:", range_start, range_end);
        for(uint32_t k = 0;k < bar_length; ++k) printf("*");
        printf("(%u)\n", buckets[i]);
    }

    free(buckets);
}
