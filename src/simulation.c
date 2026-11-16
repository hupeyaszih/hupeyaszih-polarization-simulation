#include "simulation.h"
#include "globals.h"
#include "hmath.h"
#include "logger.h"
#include <stdlib.h>

void init_simulation(struct simulation *simulation, struct config *config) {
    simulation->config = *config;
    simulation->step = 0;

    srand(config->seed);

    simulation->nodes = calloc(config->N, sizeof(struct node));
    simulation->belief_buffer = calloc(config->N, sizeof(int32_t));
    simulation->dynamic_reputation_buffer = calloc(config->N, sizeof(uint32_t));

    for(uint32_t i = 0; i < config->N; ++i) {
        struct node *node = simulation->nodes + i;
        node->id = i;
    }

    for(uint32_t i = 0; i < config->N; ++i) {
        struct node *node = simulation->nodes + i;
        node->belief = globals_convert_float_to_int32(simulation_get_random_float_between_neg1_1());
        node->persuasiveness = simulation_get_random_number(config->min_persuasiveness, config->max_persuasiveness);
        node->stubbornness = simulation_get_random_number(config->min_stubbornness, config->max_stubbornness);
        node->openness = simulation_get_random_number(config->min_openness, config->max_openness);
        node->dynamic_reputation = 0;

        uint32_t degree = simulation_get_random_number(config->initial_min_degree, config->initial_max_degree);
        node->edge_capacity = degree * 2;
        node->edges = calloc(node->edge_capacity, sizeof(struct edge));

        for(uint32_t k = 0; k < degree; ++k) {
            uint32_t target_index = simulation_get_random_number(0, simulation->config.N - 1);

            if(target_index >= node->id) {
                ++target_index;
            }
            struct node *dest = simulation->nodes + target_index;
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
    free(simulation->belief_buffer);
    free(simulation->dynamic_reputation_buffer);
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


void simulation_next_step(struct simulation *simulation) {
    if(NULL == simulation) return;
    ++simulation->step;

    // Create/Remove Edges - 1
    
    // Calculate New Beliefs - 2
    for(uint32_t i = 0;i < simulation->config.N; ++i) {
        const struct node *node = simulation->nodes + i;

        int32_t belief_i = node->belief;
        uint32_t stubbornness_i = H_U8_TO_U32(node->stubbornness);

        int64_t total_delta = 0;
        for(uint32_t j = 0;j < node->edge_count; ++j) {
            uint32_t neighbor_id = node->edges[j].destination_id;
            const struct node *neigbor = simulation->nodes + neighbor_id;

            int32_t belief_j = neigbor->belief;
            uint32_t persuasiveness_j = H_U8_TO_U32(neigbor->persuasiveness);
            uint32_t dynamic_reputation_j = neigbor->dynamic_reputation;


            uint32_t repulsion_constant = simulation->config.repulsion_constant;

            int32_t dist = belief_j - belief_i;
            int32_t abs_dist = abs(dist);

            int8_t repulsion = (repulsion_constant >= abs_dist / 2) * 2 - 1;

            uint64_t persuasion = (uint64_t)((uint64_t)persuasiveness_j + (uint64_t)dynamic_reputation_j) / 2;
            uint64_t stb = (uint64_t)(UINT32_MAX - stubbornness_i);
            uint32_t W = (uint32_t)((persuasion * stb) >> 32);

            int64_t delta_belief = (int64_t)W * repulsion * (int64_t)dist;
            total_delta += delta_belief;
        }

        int64_t new_belief = total_delta + (int64_t) node->belief;
        new_belief = hclamp_i64(new_belief, INT32_MIN, INT32_MAX);
        simulation->belief_buffer[i] = new_belief;
    }
    
    // Assign New Beliefs - 3
    for(uint32_t i = 0;i < simulation->config.N; ++i) {
        struct node *node = simulation->nodes + i;
        node->belief = simulation->belief_buffer[i];
    }

    // Calculate and Assign New Dynamic Reputations - 4

    if(0 != simulation->step % simulation->config.save_interval) return;
    logger_save_edges(simulation);
    logger_save_nodes(simulation);
}
