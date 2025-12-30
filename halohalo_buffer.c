#include <stdint.h>
#include <pigpio.h>
#include <stdio.h>
#include <string.h>


#include "halohalo_buffer.h"
#include "komplex_budov_data.h"
#include "deda.h"

/* 
	gpioSetMode(1, P_OUT); //data/command
	gpioSetMode(16, P_OUT); //rst
*/

int nokia_init()
{
    if(deda_nokia_init() < 0) { return -1; }

    set_display_y(0);
    set_display_x(0);

    mentalni_ocista();
    
    return 0;
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
    //call deda_flush some or 
}