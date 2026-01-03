#include <stdint.h>
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
    //printf("hi from nokia point green fn!%d\n\n", 888); 

    if(xy.x < 0 || xy.x > NOKIA_WIDTH || xy.y < 0 || xy.y > NOKIA_HEIGHT) { return; }

    int index = xy.x + (xy.y / 8) * NOKIA_WIDTH;
    frame_buffer->buffer[index] |= (1 << (xy.y % 8));
}

void nokia_draw_line(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end, int width)
{
    int x0 = xy_start.x;
    int y0 = xy_start.y;
    int x1 = xy_end.x;
    int y1 = xy_end.y;

    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;

    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx + dy;

     while (1)
    {
        nokia_point(frame_buffer, (goto_room_t){x0, y0});

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }

    return;
}



void nokia_draw_rectal(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end, uint8_t fill) 
{
    nokia_draw_line(frame_buffer, xy_start, (goto_room_t){xy_end.x, xy_start.y}, 0);
    nokia_draw_line(frame_buffer, xy_start, (goto_room_t){xy_start.x, xy_end.y}, 0);
    nokia_draw_line(frame_buffer, (goto_room_t){xy_start.x, xy_end.y}, xy_end, 0);
    nokia_draw_line(frame_buffer, (goto_room_t){xy_end.x, xy_start.y}, xy_end, 0);

    if(fill)
    {
        int rect_width = xy_end.x - xy_start.x;

        for(int o = 0; o < rect_width; o++)
        {
            nokia_draw_line(frame_buffer, (goto_room_t){xy_start.x + o, xy_start.y}, (goto_room_t){xy_start.x + o, xy_end.y}, 0);
        }
    }

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