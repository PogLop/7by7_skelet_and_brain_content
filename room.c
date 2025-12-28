#include "room.h"
#include "komplex_budov_data.h"
#include <stdio.h>

frame_buffer_t bff = {0};

goto_room_t entrance_update(room_ctx_t *ctx)
{
    //TETS
    goto_room_t navigator_result = {0, 0};
    goto_room_t some_xy = {10, 10};

    if(ctx->pnuky[1].pnuk_delta == 1) 
    {
        ctx->nokia_render->point(&bff, some_xy);
        navigator_result.y -= 1;
        ctx->pnuky[1].pnuk_delta = 0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!s
        
    }
    if(ctx->pnuky[1].pnuk_delta == -1)
    {
        navigator_result.y += 1;
        ctx->pnuky[1].pnuk_delta = 0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    //if(ctx->pnuky->btn_stat == 1) navigator_result.x += 1;
    

    printf("cau");

    return navigator_result;
}
//hi
//tpda
//today
//mhm