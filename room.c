#include "room.h"
#include "halohalo_buffer.h"
#include "komplex_budov_data.h"
#include <stdio.h>

goto_room_t entrance_update(room_ctx_t *ctx)
{
    //TETS
    goto_room_t navigator_result = {ctx->menu_x, ctx->menu_y};

    if(ctx->pnuky[1].pnuk_delta != 0) 
    {
        navigator_result.x += ctx->pnuky[1].pnuk_delta;
    }
    if(ctx->pnuky[2].pnuk_delta != 0) 
    {
        navigator_result.y += ctx->pnuky[2].pnuk_delta;
    }
    
    //!!
    
    //!!

    //printf("x %d y %d\n", navigator_result.x, navigator_result.y);
    
    return navigator_result;
}
//hi
//tpda
//today
//mhm