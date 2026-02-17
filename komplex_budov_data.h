#pragma once

//pardon za tenhle soubor
//#include "miniosc/miniosc.h" to uz je historie
#include "misk/fudis.h"
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
    uint8_t o_buffer[NOKIA_FRAMEBUFFER_SIZE];
}frame_buffer_t; //+-1kb


typedef struct buffer_render_nokia{
    int (*init)();
    //int nokia_de_init(buffer_render_nokia_t* render_guy); //?

    void (*draw_rectal)(frame_buffer_t* buffer, goto_room_t xy, goto_room_t width_xy, uint8_t fill);
    void (*draw_line)(frame_buffer_t* buffer, goto_room_t xy_start, goto_room_t xy_end, int width);
    void (*circle)(frame_buffer_t* buffer, goto_room_t xy, int d); //woaaah kolo (nefunguje, spíš není implementováno)
    void (*point)(frame_buffer_t* buffer, goto_room_t xy);
    
    //data_buffer pointer na array (buffer)
    void (*draw_misc_buffer)(frame_buffer_t* buffer, int *data_buffer, int datat_buffer_w, int datat_buffer_h, goto_room_t origin);

    void (*clear)(frame_buffer_t* buffer);
    void (*framebuffer_flush)(frame_buffer_t* buffer);
}buffer_render_nokia_t;


typedef struct pnuk_data{
    volatile int16_t pnuk_val;
    volatile int8_t pnuk_delta;
    volatile int8_t btn_stat;
}pnuk_data_t;


typedef struct room_ctx {
    buffer_render_nokia_t *nokia_render;
    int16_t (*matrix_state)[MATRIX_SIZE][MATRIX_SIZE];
    int16_t (*matrix_pnuk_state)[MATRIX_SIZE][MATRIX_SIZE][PNUKU_JE_TOLIK];
    t_foodis *food;
    pnuk_data_t *pnuky;
    int menu_x;
    int menu_y;
    frame_buffer_t *fb;
}room_ctx_t;


typedef goto_room_t (*updte_slave_fn_make_him_better)(room_ctx_t *);