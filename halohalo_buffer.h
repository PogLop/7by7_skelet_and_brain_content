#pragma once

#include "komplex_budov_data.h"
#include <stdint.h>

int nokia_init(); //do not use in rooms
//int nokia_de_init(frame_buffer_t* frame_buffer); //?

void nokia_point(frame_buffer_t* frame_buffer, goto_room_t xy);

void draw_line_high(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end);
void draw_line_low(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end);
void nokia_draw_line(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end, int width);

void nokia_draw_rectal(frame_buffer_t* frame_buffer, goto_room_t xy_start, goto_room_t xy_end);

void nokia_circle(frame_buffer_t* frame_buffer, goto_room_t xy, int d); //woaaah kolo

void nokia_clear(frame_buffer_t* frame_buffer);
void nokia_framebuffer_flush(frame_buffer_t* frame_buffer);