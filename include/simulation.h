#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include "pcg_basic.h"
#include <stdint.h>

struct edge {
    uint32_t source_id;
    uint32_t destination_id;
};

struct node {
    uint32_t id;
    int32_t belief;

    uint8_t persuasiveness;
    uint8_t stubbornness;
    uint8_t openness;
    uint8_t dynamic_reputation;

    uint16_t edge_count;
    uint16_t edge_capacity;
    struct edge *edges;
};

struct simulation {
    struct node *nodes;
    int32_t *belief_buffer;
    struct config config;
    uint64_t step;
};

void delete_node(struct node *node);

void init_simulation(struct simulation *simulation, struct config *config);
void simulation_next_step(struct simulation *simulation);

void delete_simulation(struct simulation *simulation);

static inline uint32_t simulation_get_random_number(uint32_t min, uint32_t max) {
    if(max <= min) return min;
    return pcg32_random() % (max - min) + min;
}

static inline float simulation_get_random_float_between_0_1() {
    return (float) pcg32_random() / (float) UINT32_MAX;
}

static inline float simulation_get_random_float_between_neg1_1() {
    return (float) pcg32_random() / ((float) UINT32_MAX / 2.0f) - 1.0f;
}

void simulation_node_add_edge(struct node *source_node, struct node *destination_node);
void simulation_node_remove_edge(struct node *source_node, uint32_t edge_id);

struct edge *simulation_node_find_edge(struct node *source_node, struct node *destination_node);

struct statistics {
    int32_t average_belief;

    uint32_t average_dynamic_reputation;

    const struct simulation *simulation;
    uint64_t belief_variance;
    uint64_t step;
};
struct statistics simulation_calculate_statistics(const struct simulation *simulation);
#endif
