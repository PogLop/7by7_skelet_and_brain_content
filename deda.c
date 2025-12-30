#include <stdint.h>
#include <pigpio.h>
#include <string.h>

#include "deda.h"



static int spi;

int deda_nokia_init()
{
    spi = spiOpen(0, 96000, 0);

    if(spi < 0)
    {
        return -1;
    }

    uint8_t commands[] = {
        0x21, //h=1
        0xC0, //voltage
        0x07, //some temp
        0x13, //bias system 1:48
        0x20, //h=0
        0x0C //normal 
    };

    gpioWrite(RST_PIN, 0);
    gpioDelay(500000);
    gpioWrite(RST_PIN, 1);

    for(int g = 0; g < (int)(sizeof(commands) / sizeof(commands[0])); g++)
    {
        gpioWrite(CE_PIN, 0);
        gpioWrite(DC_PIN, 0);
        spiWrite(spi, (char*)&commands[g], 1);
        gpioWrite(CE_PIN, 1);
    }

    return 0;
}

void set_display_x(uint8_t value)
{
    if(value > 83){ return; }

    uint8_t cmd = 0x80 | value;

    gpioWrite(CE_PIN, 0);
    gpioWrite(DC_PIN, 0);
    spiWrite(spi, (char*)&cmd, 1);
    gpioWrite(CE_PIN, 1);
}

void set_display_y(uint8_t value)
{
    if(value > 5){ return; }
    
    uint8_t cmd = 0x40 | value;
    
    gpioWrite(CE_PIN, 0);
    gpioWrite(DC_PIN, 0);
    spiWrite(spi, (char*)&cmd, 1);
    gpioWrite(CE_PIN, 1);
}

/*
void test_write()
{
    uint8_t data = 0xFF;

    set_display_x(0);
    set_display_y(0);

    gpioWrite(CE_PIN, 0);
    gpioWrite(DC_PIN, 1);

    spiWrite(spi, (char*)&data, 1);

    gpioWrite(CE_PIN, 1);
    
    gpioDelay(2000);
    
    uint8_t test[84];
    memset(test, 0xFF, sizeof(test));
    
    
    for(uint8_t d = 0; d < NOKIA_BANKS_Y; d++)
    {
        set_display_y(d);
        gpioWrite(CE_PIN, 0);
        gpioWrite(DC_PIN, 1);
        spiWrite(spi, (char*)&test, sizeof(test));
        gpioWrite(CE_PIN, 1);
    }
    
    return;
}
*/


void mentalni_ocista()
{
    uint8_t line_buffer[NOKIA_BANKS_X];

    memset(line_buffer, 0x0, sizeof(line_buffer));
    
    for(uint8_t d = 0; d < NOKIA_BANKS_Y; d++)
    {
        set_display_y(d);
        gpioWrite(CE_PIN, 0);
        gpioWrite(DC_PIN, 1);
        spiWrite(spi, (char*)&line_buffer, sizeof(line_buffer));
        gpioWrite(CE_PIN, 1);
    }

    return;
}

void deda_nokia_buffer_flush(frame_buffer_t *frame_buffer)
{
    for(uint8_t d = 0; d < NOKIA_BANKS_Y; d++)
    {
        for(int t = (d * NOKIA_BANKS_X); t < (d * NOKIA_BANKS_X + NOKIA_BANKS_X); t++)
        {
            set_display_y(d);

            gpioWrite(CE_PIN, 0);
            gpioWrite(DC_PIN, 1);

            spiWrite(spi, (char*)&frame_buffer->buffer[t], 1);
            
            gpioWrite(CE_PIN, 1);
        }
    }
    
    return;
}