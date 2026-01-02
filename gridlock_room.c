#include "gridlock_room.h"
#include "komplex_budov_data.h"
#include "halohalo_buffer.h"
#include <string.h>

goto_room_t gridlock_update(room_ctx_t *ctx)
{
    goto_room_t return_nav_state = {
        ctx->menu_x,
        ctx->menu_y        
    };

    unsigned int matrix_value_array[MATRIX_SIZE][MATRIX_SIZE][PNUKU_JE_TOLIK];
    memset(matrix_value_array, 0, sizeof(matrix_value_array));

    int grid_cell = 5;
    int grid_scale = (MATRIX_SIZE * grid_cell);

    for(int g = 0; g <= MATRIX_SIZE; g++)
    {
        nokia_draw_line(ctx->fb, (goto_room_t){g * grid_cell, 0}, (goto_room_t){g * grid_cell, grid_scale}, 0);
        nokia_draw_line(ctx->fb, (goto_room_t){0, g * grid_cell}, (goto_room_t){grid_scale, g * grid_cell}, 0);
    }

    nokia_framebuffer_flush(ctx->fb);

    return return_nav_state;
}