#pragma once

#include "komplex_budov_data.h"

int nokia_init(buffer_render_nokia_t* frame_buffer);
//int nokia_de_init(buffer_render_nokia_t* frame_buffer); //?

void nokia_point(buffer_render_nokia_t* frame_buffer, goto_room_t xy);

void nokia_draw_line(buffer_render_nokia_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end, int width);

void nokia_draw_rectal(buffer_render_nokia_t* frame_buffer, goto_room_t xy, goto_room_t width_xy);

void nokia_circle(buffer_render_nokia_t* frame_buffer, goto_room_t xy, int d); //woaaah kolo

void nokia_clear(buffer_render_nokia_t* frame_buffer);
void nokia_framebuffer_flush(buffer_render_nokia_t* frame_buffer);