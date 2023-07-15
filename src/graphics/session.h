#pragma once
#include "buffer.h"
#include "drawcall.h"

#define ADS_DRAWCALL_BUFFER_SIZE 128

typedef struct
{
    scrbuf_t* buf;
    scrbuf_t* temp_buf;

    uint16_t drawcall_count;
    drawcall_t calls[ADS_DRAWCALL_BUFFER_SIZE];
} ads_session_t;

ads_session_t* ads_create_session(scrbuf_t* buffer, scrbuf_t* temp_buffer);
void ads_append_drawcall(ads_session_t* session, drawcall_t call);
void ads_process_drawcalls(ads_session_t* session);
