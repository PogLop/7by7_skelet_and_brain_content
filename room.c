#include "room.h"
#include "komplex_budov_data.h"

frame_buffer_t bff = {0};

goto_room_t update(room_ctx_t *ctx)
{
    //TETS
    goto_room_t navigator_result = {0, 0};
    goto_room_t some_xy = {10, 10};

    if(ctx->pnuky[1].pnuk_delta == 1) 
    {
        ctx->nokia_render->point(&bff, some_xy);
        navigator_result.y -= 1;

    }
    if(ctx->pnuky->btn_stat == 1) navigator_result.x += 1;

    return navigator_result;
}
//hi
//tpda
//today
//mhm