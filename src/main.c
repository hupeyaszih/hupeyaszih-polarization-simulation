#include "argument_parser.h"
#include "config.h"
#include "logger.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello from hupeyaszih-polarization-simulation (C)!\n");
    struct config config = config_init_default_config();
    argument_parser_parse_config(&config, argc, argv);
    logger_print_config(&config);

    printf("Hupeyaszih Polarization Simulation is starting...\n");
    return 0;
}
