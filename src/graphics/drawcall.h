#pragma once

#include "buffer.h"
#include "primitives.h"

typedef struct
{
    char type;
    primitive_t object;
    uint32_t color;
} drawcall_t;
drawcall_t drawcall_from_label(label_t object, uint32_t color);
drawcall_t drawcall_from_line(line_t object, uint32_t color);
drawcall_t drawcall_from_tri(tri_t object, uint32_t color);
drawcall_t drawcall_from_rect(rect_t object, uint32_t color);

void akr_handle_drawcall(drawcall_t* call, scrbuf_t* destBuffer, scrbuf_t* tempBuffer);
