#include "drawcall.h"

drawcall_t create_drawcall(char type, primitive_t object, uint32_t color)
{
    drawcall_t call;
    call.type = type;
    call.object = object;
    call.color = color;
    return call;
}
drawcall_t drawcall_from_label(label_t object, uint32_t color)
{
    return create_drawcall(PRIMITIVE_TEXT, *(primitive_t*)&object, color);
}
drawcall_t drawcall_from_line(line_t object, uint32_t color)
{
    return create_drawcall(PRIMITIVE_LINE, *(primitive_t*)&object, color);
}
drawcall_t drawcall_from_tri(tri_t object, uint32_t color)
{
    return create_drawcall(PRIMITIVE_TRI, *(primitive_t*)&object, color);
}
drawcall_t drawcall_from_rect(rect_t object, uint32_t color)
{
    return create_drawcall(PRIMITIVE_RECT, *(primitive_t*)&object, color);
}

void akr_handle_drawcall(drawcall_t* call, scrbuf_t* destBuffer, scrbuf_t* tempBuffer)
{
    switch (call->type)
    {
        case PRIMITIVE_TEXT:
            scrbuf_DrawText(tempBuffer,
                            call->object.as_label.x,
                            call->object.as_label.y,
                            call->object.as_label.text);
            return;
        case PRIMITIVE_POINT:
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
        default:
            printf("DRAWCALL TYPE NOT IMPLEMENTED\n");
            return; // TODO
    }
}
