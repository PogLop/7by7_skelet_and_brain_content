#include "pnuk_driver.h"
#include "komplex_budov_data.h"
#include "pnuk.h"

#include <stddef.h>
#include <stdio.h>

pnuk_data_t return_data[PNUKU_JE_TOLIK];
pnukT *lidi[PNUKU_JE_TOLIK];


void pnuk_callback_ABC(int value, int id)
{
    pnuk_data_t *data = &return_data[id];
    
    data->pnuk_val += value;
    data->pnuk_delta = value; //každá místnost musí po přečtení delta (levo nebio pravo) tuto hodnotu nastavit na 0!
    //brouku
    printf("%d\n", data->pnuk_val);
}

void pnuk_btn_callback_ABC(int value, int id)
{
    pnuk_data_t *data = &return_data[id];
    if(value) data->btn_stat = value;
    printf("%d knoflik\n", value);
}

void pnuk_init(pnuk_config_t init_data[PNUKU_JE_TOLIK])
{
    for(int c = 0; c < PNUKU_JE_TOLIK; c++)
    {
        return_data[c].pnuk_delta = 0;
        return_data[c].pnuk_val = 0;
        return_data[c].btn_stat = 0;

        lidi[c] = pnukPnuk(
            c, 
            init_data[c].gpioA, 
            init_data[c].gpioB,
            init_data[c].knoflPin,
            pnuk_callback_ABC, 
            pnuk_btn_callback_ABC
        );
    }
}

pnuk_data_t* pnuk_get_data(void)
{
    return return_data;
}

void pnuk_driver_de_init()
{
    for(int u = 0; u < PNUKU_JE_TOLIK; u++)
    {
        pnukOver(lidi[u]);
        lidi[u] = NULL;
    }
}
