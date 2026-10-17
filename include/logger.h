#ifndef LOGGER_H
#define LOGGER_H

#include "config.h"
#include "simulation.h"

void logger_print_config(struct config *config);

void logger_save_edges(const struct simulation *simulation);
void logger_save_nodes(const struct simulation *simulation);

#endif
