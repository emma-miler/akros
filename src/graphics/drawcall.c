#include "drawcall.h"

drawcall_t akr_create_drawcall(primitive_t object, uint32_t color)
{
    drawcall_t call;
    call.object = object;
    call.color = color;
    return call;
}

void akr_handle_drawcall(drawcall_t* call, scrbuf_t* destBuffer, scrbuf_t* tempBuffer)
{
    switch (call->object.base.type)
    {
        case PRIMITIVE_POINTD:
            printf("DRAWCALL TYPE NOT IMPLEMENTED\n");
            return;
        case PRIMITIVE_LINE:
            printf("DRAWCALL TYPE NOT IMPLEMENTED\n");
            return; // TODO
        case PRIMITIVE_RECT:
            scrbuf_DrawRect(tempBuffer,
                            call->object.as_rect.x,
                            call->object.as_rect.y,
                            call->object.as_rect.x + call->object.as_rect.width,
                            call->object.as_rect.y + call->object.as_rect.height,
                            call->color);
            break;
        case PRIMITIVE_TRI:
            printf("DRAWCALL TYPE NOT IMPLEMENTED\n");
            return; // TODO
    }
}
