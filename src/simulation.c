#include "simulation.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>

void init_simulation(struct simulation *simulation, struct config *config) {
    simulation->config = *config;
    simulation->time = 0;

    srand(config->seed);

    simulation->nodes = calloc(config->N, sizeof(struct node));
    for(uint32_t i = 0; i < config->N; ++i) {
        struct node *node = simulation->nodes + i;
        node->id = i;

        node->belief = simulation_get_random_number(0, globals_convert_float_to_uint32(1.0f));
        node->persuasiveness = simulation_get_random_number(config->min_persuasiveness, config->max_persuasiveness);
        node->stubbornness = simulation_get_random_number(config->min_stubbornness, config->max_stubbornness);
        node->openness = simulation_get_random_number(config->min_openness, config->max_openness);
        node->dynamic_reputation = 0;

        uint32_t degree = simulation_get_random_number(config->initial_min_degree, config->initial_max_degree);
        node->edge_count = degree;
        node->edge_capacity = node->edge_count;
        node->edges = calloc(node->edge_capacity, sizeof(struct edge));

        for(uint32_t k = 0; k < degree; ++k) {
            struct node *dest = simulation->nodes + simulation_get_random_number(0, simulation->config.N);
            simulation_node_add_edge(node, dest);
        }
    }
}

void delete_node(struct node *node) {
    if(NULL == node) return;
    free(node->edges);
}

void delete_simulation(struct simulation *simulation) {
    if(NULL == simulation) return;
    for(uint32_t i = 0;i < simulation->config.N; ++i) {
        struct node *node = simulation->nodes + i;
        delete_node(node);
    }
    free(simulation->nodes);
}

void simulation_node_add_edge(struct node *source_node, struct node *destination_node) {
    if(NULL == source_node || NULL == destination_node) return;
    if(NULL != simulation_node_find_edge(source_node, destination_node)) return;

    if(source_node->edge_capacity <= source_node->edge_count) {
        source_node->edge_capacity *= 2;
        struct edge *temp =  realloc(source_node->edges, sizeof(struct edge) * source_node->edge_capacity);
        if(NULL == temp) return;
        source_node->edges = temp;
    }

    uint32_t id = source_node->edge_count;
    source_node->edges[id].source_id = source_node->id;
    source_node->edges[id].destination_id = destination_node->id;
    ++source_node->edge_count;
}

void simulation_node_remove_edge(struct node *source_node, uint32_t edge_id) {
    if(NULL == source_node || edge_id < 0 || edge_id >= source_node->edge_count) return;
    source_node->edges[edge_id] = source_node->edges[source_node->edge_count - 1];
    --source_node->edge_count;
}

struct edge *simulation_node_find_edge(struct node *source_node, struct node *destination_node) {
    if(NULL == source_node || NULL == destination_node) return NULL;

    for(uint32_t i = 0;i < source_node->edge_count; ++i) {
        struct edge *edge = source_node->edges + i;
        if(NULL == edge) continue;
        if(edge->destination_id == destination_node->id) return edge;
    }

    return NULL;
}
