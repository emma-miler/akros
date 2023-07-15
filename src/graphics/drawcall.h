#pragma once

#include "buffer.h"
#include "primitives.h"

typedef struct
{
    primitive_t object;
    uint32_t color;
} drawcall_t;
drawcall_t akr_create_drawcall(primitive_t object, uint32_t color);

void akr_handle_drawcall(drawcall_t* call, scrbuf_t* destBuffer, scrbuf_t* tempBuffer);
