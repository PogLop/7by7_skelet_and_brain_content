#include "gridlock_room.h"
#include "komplex_budov_data.h"
#include "halohalo_buffer.h"
#include "misk/fudis.h"
#include "misk/nehet.h"


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



goto_room_t cursor = {0, 0};

bool value_mode = false;
int last_btn2_sate = 0;

goto_room_t gridlock_update(room_ctx_t *ctx)
{
    int h;

    goto_room_t return_nav_state = {
        ctx->menu_x,
        ctx->menu_y        
    };


    memset(ctx->fb->buffer, 0x0, sizeof(ctx->fb->buffer));
    

    char _send_pnuk[32];
    char _send_m[64];
    char *_tmp;
    

    uint8_t grid_cell = 5;
    uint8_t grid_scale = (MATRIX_SIZE * grid_cell);


    //matrix back buffer
    int16_t _mx_b_buff[MATRIX_SIZE][MATRIX_SIZE];
    memset(_mx_b_buff, 0, sizeof(_mx_b_buff));



    //move cursor around
    if(!value_mode)
    {
        if(ctx->pnuky[1].pnuk_delta != 0) 
        {
            if(ctx->pnuky[1].pnuk_val < MATRIX_SIZE && ctx->pnuky[1].pnuk_val >= 0)
            {
                cursor.x = ctx->pnuky[1].pnuk_val;
            }    
        }
        
        if(ctx->pnuky[2].pnuk_delta != 0) 
        {
            if(ctx->pnuky[2].pnuk_val < MATRIX_SIZE && ctx->pnuky[2].pnuk_val >= 0)
            {
                cursor.y = ctx->pnuky[2].pnuk_val;
            }    
        }
    }



    //cursor not moving
    //able to change one of 3 parameter values on given grid location
    //instantly sent to pure data for further
    //manipulation
    if(value_mode)
    {
        for(h = 0; h < PNUKU_JE_TOLIK; h++)
        {
            if(ctx->pnuky[h].pnuk_delta != 0)
            {
                ctx->matrix_pnuk_state[0][cursor.x][cursor.y][h] += ctx->pnuky[h].pnuk_delta;

                //format--> "list x y id val";
                ////////////////
                snprintf(_send_pnuk, sizeof(_send_pnuk), "list\x20%d\x20%d\x20%d\x20%d;", 
                    cursor.x, 
                    cursor.y, 
                    h,
                    ctx->matrix_pnuk_state[0][cursor.x][cursor.y][h]);

                //printf("DEBUG--> sending pnuk data: '%s'\n", _send_pnuk);

                FOODISmail(ctx->food, _send_pnuk, "/pnuky");
            }
        }

        
        ctx->pnuky[0].pnuk_delta = 0; //priste asi implementuju state machine, tohle je ass149(c) fakt
        ctx->pnuky[1].pnuk_delta = 0;
        ctx->pnuky[2].pnuk_delta = 0;
        

        //indicator, important, obey!!!
        //indicates, that user is now in value 
        //mode
        nokia_draw_rectal(ctx->fb, 
            (goto_room_t){grid_scale, grid_scale}, 
            (goto_room_t){grid_scale + 5, grid_scale + 5}, 
            1);
    }


    if(ctx->pnuky[2].btn_stat == 1 && last_btn2_sate == 0)
    {
        value_mode = !value_mode;
        
        ctx->pnuky[1].pnuk_val = cursor.x;
        ctx->pnuky[2].pnuk_val = cursor.y;

        ctx->pnuky[2].btn_stat = 0;
    }
    last_btn2_sate = ctx->pnuky[2].btn_stat;



    //send matrix data to pure data
    //only if it changed
    //else it could lag pure data DSP or whateaver
    if(!CMPbuffer((uint8_t *)ctx->matrix_state, (uint8_t *)_mx_b_buff, (MATRIX_SIZE * MATRIX_SIZE)))
    {
        _tmp = FORMATRIX((int16_t *)ctx->matrix_state, 7, 7);

        snprintf(_send_m, sizeof(_send_m), "list\x20%s;", _tmp);
    
        FOODISmail(ctx->food, _send_m, "/matrix");
        
        memcpy(&_mx_b_buff, ctx->matrix_state, sizeof(_mx_b_buff));

        
        free(_tmp);
    }


    //draw xxxxxxxxx xoxo mwuah
    for(int a = 0; a < MATRIX_SIZE; a++)
    {
        for(int b = 0; b < MATRIX_SIZE; b++)
        {
            if(ctx->matrix_state[0][b][a])
            {
                nokia_draw_line(ctx->fb, 
                    (goto_room_t){a*grid_cell, b*grid_cell}, 
                    (goto_room_t){a*grid_cell+grid_cell, b*grid_cell+grid_cell}, 
                    0);
            }
        }
    }


    //draw the grid
    for(int g = 0; g <= MATRIX_SIZE; g++)
    {
        nokia_draw_line(ctx->fb, 
            (goto_room_t){g * grid_cell, 0}, 
            (goto_room_t){g * grid_cell, grid_scale}, 
            0);
        
        nokia_draw_line(ctx->fb, 
            (goto_room_t){0, g * grid_cell}, 
            (goto_room_t){grid_scale, g * grid_cell}, 
            0);
    }


    goto_room_t draw_pos = {
        cursor.x * grid_cell,
        cursor.y * grid_cell
    };


    nokia_draw_rectal(ctx->fb, 
        draw_pos, 
        (goto_room_t){draw_pos.x + grid_cell, draw_pos.y + grid_cell}, 
        1);


    nokia_framebuffer_flush(ctx->fb);

    return return_nav_state; //importnatan
}