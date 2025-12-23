#include "room.h"
#include "komplex_budov_data.h"

goto_room_t update(room_ctx_t *ctx)
{
    //TETS
    goto_room_t navigator_result = {0, 0};
    
    if(ctx->pnuky[1].pnuk_delta == 1) navigator_result.y -= 1;
    if(ctx->pnuky->btn_stat == 1) navigator_result.x += 1;

    return navigator_result;
}