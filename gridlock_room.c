#include "gridlock_room.h"
#include "komplex_budov_data.h"
#include "halohalo_buffer.h"
#include "miniosc/miniosc.h"
#include <stdio.h>
#include <string.h>


goto_room_t cursor = {0, 0};

goto_room_t gridlock_update(room_ctx_t *ctx)
{
    memset(ctx->fb->buffer, 0x0, sizeof(ctx->fb->buffer));
    
    goto_room_t return_nav_state = {
        ctx->menu_x,
        ctx->menu_y        
    };
    
    
    int grid_cell = 5;
    int grid_scale = (MATRIX_SIZE * grid_cell);
    
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

    for(int a = 0; a < MATRIX_SIZE; a++)
    {
        for(int b = 0; b < MATRIX_SIZE; b++)
        {
            char osc_addr[100];
            snprintf(osc_addr, sizeof(osc_addr), "/matrix/r%d/c%d", a, b);

            minioscSend(ctx->pane_osc, osc_addr, ",i", ctx->matrix_state[0][a][b]);

            if(ctx->matrix_state[0][b][a])
            {
                nokia_draw_line(ctx->fb, (goto_room_t){a*grid_cell, b*grid_cell}, (goto_room_t){a*grid_cell+grid_cell, b*grid_cell+grid_cell}, 0);
            }
        }
    }

    for(int g = 0; g <= MATRIX_SIZE; g++)
    {
        nokia_draw_line(ctx->fb, (goto_room_t){g * grid_cell, 0}, (goto_room_t){g * grid_cell, grid_scale}, 0);
        nokia_draw_line(ctx->fb, (goto_room_t){0, g * grid_cell}, (goto_room_t){grid_scale, g * grid_cell}, 0);
    }

    goto_room_t draw_pos = {
        cursor.x * grid_cell,
        cursor.y * grid_cell
    };

    nokia_draw_rectal(ctx->fb, draw_pos, (goto_room_t){draw_pos.x + grid_cell, draw_pos.y + grid_cell}, 1);

    nokia_framebuffer_flush(ctx->fb);

    //ctx->pnuky[1].pnuk_delta = 0; 
    //ctx->pnuky[2].pnuk_delta = 0; 

    return return_nav_state;
}