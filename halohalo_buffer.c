#include <stdint.h>
#include <pigpio.h>
#include <stdio.h>
#include <string.h>


#include "halohalo_buffer.h"
#include "komplex_budov_data.h"


#define RST_PIN 16
#define DC_PIN 26
#define CE_PIN 25

#define NOKIA_BANKS_Y 5
#define NOKIA_BANKS_X 83

/* 
	gpioSetMode(1, P_OUT); //data/command
	gpioSetMode(16, P_OUT); //rst
*/

static int spi;

int nokia_init()
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
    gpioDelay(10);
    gpioWrite(RST_PIN, 1);

    for(int g = 0; g < sizeof(commands); g++)
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
*/
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
    
    gpioWrite(CE_PIN, 0);
    gpioWrite(DC_PIN, 1);

    spiWrite(spi, (char*)&test, sizeof(test));

    gpioWrite(CE_PIN, 1);

    return;
}

void nokia_point(frame_buffer_t* frame_buffer, goto_room_t xy)
{
    printf("hi from nokia point green fn!%d\n\n", 888);

    if(xy.x < 0 || xy.x > NOKIA_WIDTH || xy.y < 0 || xy.y > NOKIA_HEIGHT) { return; }

    int index = xy.x + (xy.y / 8) * NOKIA_WIDTH;
    frame_buffer->buffer[index] |= (1 << (xy.y % 8));
}

void nokia_draw_line(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end, int width)
{
    return;
}

void nokia_draw_rectal(frame_buffer_t* frame_buffer, goto_room_t xy, goto_room_t width_xy) 
{
    return;
}

void nokia_circle(frame_buffer_t* frame_buffer, goto_room_t xy, int d)
{
    return;
}

void nokia_clear(frame_buffer_t* frame_buffer)
{
    return;
}

void nokia_framebuffer_flush(frame_buffer_t* frame_buffer)
{
    gpioWrite(CE_PIN, 0);
    gpioWrite(DC_PIN, 1);    
        
    spiWrite(spi, (char*)&frame_buffer->buffer, NOKIA_WIDTH);
    
    gpioWrite(CE_PIN, 1);
    
    return;
}