#include <stdint.h>
#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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


void draw_line_high(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end)
{
    int dx = xy_end.x - xy_start.x;
    int dy = xy_end.y - xy_start.y;
    int xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = (2 * dx) - dy;
    int x = xy_start.x;

    for(int y = xy_start.y; y < xy_end.y; y++)
    {
        nokia_point(frame_buffer, (goto_room_t){x, y});

        if(D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
    }

    return;
}
void draw_line_low(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end)
{
    int dx = xy_end.x - xy_start.x;
    int dy = xy_end.y - xy_start.y;
    int yi = 1;
    
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    
    int D = (2 * dy) - dx;
    int y = xy_start.y;
    
    for(int x = xy_start.x; x < xy_end.x; x++)
    {
        nokia_point(frame_buffer, (goto_room_t){x, y});
    
        if(D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
    }
    
    return;
}

void nokia_draw_line(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end, int width)
{
    int x0 = xy_start.x;
    int y0 = xy_start.y;
    int x1 = xy_end.x;
    int y1 = xy_end.y;

    if(abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
        {
            draw_line_low(frame_buffer, xy_end, xy_start);
        } else {
            draw_line_low(frame_buffer, xy_start, xy_end);
        }
    } else {
        if (y0 > y1)
        {
            draw_line_high(frame_buffer, xy_end, xy_start);
        } else {
            draw_line_high(frame_buffer, xy_start, xy_start);
        }
    }

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
    mentalni_ocista();
    return;
}

void nokia_framebuffer_flush(frame_buffer_t* frame_buffer)
{
    deda_nokia_buffer_flush(frame_buffer);
    //call deda_flush some or 
}