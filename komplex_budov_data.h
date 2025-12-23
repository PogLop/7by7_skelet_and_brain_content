#pragma once

#include "miniosc/miniosc.h"
#include <stdint.h>

#define PNUKU_JE_TOLIK 3
#define MATRIX_SIZE 7
#define NOKIA_WIDTH 84
#define NOKIA_HEIGHT 48
#define NOKIA_FRAMEBUFFER_SIZE (NOKIA_HEIGHT * NOKIA_WIDTH) / 8

typedef struct goto_room {
    int x;
    int y;
} goto_room_t;

typedef struct frame_buffer{
    uint8_t buffer[NOKIA_FRAMEBUFFER_SIZE];
}frame_buffer_t;

typedef struct buffer_render_nokia{
    int (*nokia_init)(frame_buffer_t* buffer);
    //int nokia_de_init(buffer_render_nokia_t* render_guy); //?

    void (*draw_rectal)(frame_buffer_t* buffer, goto_room_t xy, goto_room_t width_xy);
    void (*draw_line)(frame_buffer_t* buffer, goto_room_t xy_start, goto_room_t xy_end, int width);
    void (*circle)(frame_buffer_t* buffer, goto_room_t xy, int d); //woaaah kolo
    void (*point)(frame_buffer_t* buffer, goto_room_t xy);

    void (*clear)(frame_buffer_t* buffer);
    void (*framebuffer_flush)(frame_buffer_t* buffer);
}buffer_render_nokia_t;

typedef struct pnuk_data{
    volatile int pnuk_val;
    volatile int pnuk_delta;
    volatile int btn_stat;
}pnuk_data_t;

typedef struct room_ctx {
    buffer_render_nokia_t *nokia_render;
    int matrix_state[MATRIX_SIZE][MATRIX_SIZE];
    miniosc *pane_osc;
    pnuk_data_t pnuky[PNUKU_JE_TOLIK];
}room_ctx_t;


typedef goto_room_t (*updte_slave_fn_make_him_better)(room_ctx_t *);