#pragma once

#include "komplex_budov_data.h"

typedef struct pnuk_config{
    int gpioA;
    int gpioB;
    int knoflPin;
}pnuk_config_t;

void init(pnuk_config_t init_data[PNUKU_JE_TOLIK]);

pnuk_data_t* get_data(void);

void pnuk_driver_de_init();