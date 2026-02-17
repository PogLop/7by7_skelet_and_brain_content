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
    goto_room_t return_nav_state = {
        ctx->menu_x,
        ctx->menu_y        
    };


    memset(ctx->fb->buffer, 0x0, sizeof(ctx->fb->buffer));
    
    char _send_pnuk[20];
    char _send_m[60];
    
    
    uint8_t grid_cell = 5;
    uint8_t grid_scale = (MATRIX_SIZE * grid_cell);

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

    if(value_mode)
    {
        if(ctx->pnuky[0].pnuk_delta != 0)
        {
            ctx->matrix_pnuk_state[0][cursor.x][cursor.y][0] += ctx->pnuky[0].pnuk_delta;

            snprintf(_send_pnuk, sizeof(_send_pnuk), "list\x20%d\x20%d\x20%d\x20%d;", 
                cursor.x, 
                cursor.y, 
                0,
                ctx->matrix_pnuk_state[0][cursor.x][cursor.y][0]);
            FOODISmail(ctx->food, "", "/pnuky");
        }
        
        if(ctx->pnuky[1].pnuk_delta != 0)
        {
            ctx->matrix_pnuk_state[0][cursor.x][cursor.y][1] += ctx->pnuky[1].pnuk_delta;

            snprintf(_send_pnuk, sizeof(_send_pnuk), "list\x20%d\x20%d\x20%d\x20%d;", 
                cursor.x, 
                cursor.y, 
                1,
                ctx->matrix_pnuk_state[0][cursor.x][cursor.y][1]);
            FOODISmail(ctx->food, "", "/pnuky");
        }
        
        if(ctx->pnuky[2].pnuk_delta != 0)
        {
            ctx->matrix_pnuk_state[0][cursor.x][cursor.y][2] += ctx->pnuky[2].pnuk_delta;

            snprintf(_send_pnuk, sizeof(_send_pnuk), "list\x20%d\x20%d\x20%d\x20%d;", 
                cursor.x, 
                cursor.y, 
                2,
                ctx->matrix_pnuk_state[0][cursor.x][cursor.y][2]);
            FOODISmail(ctx->food, "", "/pnuky");
        }

        
        ctx->pnuky[0].pnuk_delta = 0; //priste asi implementuju state machine, tohle je ass149(c) fakt
        ctx->pnuky[1].pnuk_delta = 0;
        ctx->pnuky[2].pnuk_delta = 0;
        
        //indicator, important, obey!!!
        nokia_draw_rectal(ctx->fb, (goto_room_t){grid_scale, grid_scale}, (goto_room_t){grid_scale + 5, grid_scale + 5}, 1);
    }


    if(ctx->pnuky[2].btn_stat == 1 && last_btn2_sate == 0)
    {
        value_mode = !value_mode;
        
        ctx->pnuky[1].pnuk_val = cursor.x;
        ctx->pnuky[2].pnuk_val = cursor.y;

        ctx->pnuky[2].btn_stat = 0;
    }
    last_btn2_sate = ctx->pnuky[2].btn_stat;


    for(int a = 0; a < MATRIX_SIZE; a++)
    {
        for(int b = 0; b < MATRIX_SIZE; b++)
        {
            //matrix/rx/cx
            //pnuky/rx/cx/px
            
            snprintf(_send_m, sizeof(_send_m), "list\x20%s;", FORMATRIX((int16_t *)ctx->matrix_state, 7, 7));
            
            FOODISmail(ctx->food, _send_m, "/matrix");

            //draw xxxxxxxxx xoxo mwuah
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

    return return_nav_state;
}