#include "room.h"
#include "komplex_budov_data.h"
#include <stdio.h>

goto_room_t entrance_update(room_ctx_t *ctx)
{
    //TETS
    goto_room_t navigator_result = {ctx->menu_x, ctx->menu_y};
    goto_room_t some_xy = {10, 10};

    if(ctx->pnuky[1].pnuk_delta == 1) 
    {
        ctx->nokia_render->point(ctx->fb, some_xy);
        navigator_result.x += 1;
        ctx->pnuky[1].pnuk_delta = 0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
    }
    if(ctx->pnuky[1].pnuk_delta == -1)
    {
        if(navigator_result.x > 0)
        {
            navigator_result.x -= 1;
        }

        ctx->pnuky[1].pnuk_delta = 0;
    }
    //if(ctx->pnuky->btn_stat == 1) navigator_result.x += 1;
    
    return navigator_result;
}
//hi
//tpda
//today
//mhm