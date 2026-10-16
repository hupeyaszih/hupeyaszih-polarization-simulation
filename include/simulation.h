#ifndef SIMULATION_H
#define SIMULATION_H

#include "config.h"
#include <stdint.h>
#include <stdlib.h>

struct edge {
    uint32_t source_id;
    uint32_t destination_id;
};

struct node {
    uint32_t id;

    uint32_t belief;
    uint32_t persuasiveness;
    uint32_t stubbornness;
    uint32_t openness;

    uint16_t edge_count;
    uint16_t edge_capacity;
    struct edge *edges;
};

struct simulation {
    struct node *nodes;
    struct config config;
};

void delete_node(struct node *node);

void init_simulation(struct simulation *simulation, struct config *config);
void delete_simulation(struct simulation *simulation);

static inline uint32_t simulation_get_random_number(uint32_t min, uint32_t max) {
    return rand() % (max - min) + min;
}

void simulation_node_add_edge(struct node *source_node, struct node *destination_node);
void simulation_node_remove_edge(struct node *source_node, uint32_t edge_id);

struct edge *simulation_node_find_edge(struct node *source_node, struct node *destination_node);

#endif
