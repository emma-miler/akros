#include "ads.h"

ads_session_t* ads_create_session(scrbuf_t* buffer, scrbuf_t* temp_buffer)
{
    ads_session_t* session = malloc(sizeof(ads_session_t));
    session->buf = buffer;
    session->temp_buf = temp_buffer;
    session->drawcall_count = 0;
    memset(session->calls, 0, sizeof(session->calls));
    return session;
}

void ads_append_drawcall(ads_session_t* session, drawcall_t call)
{
    session->calls[session->drawcall_count] = call;
    session->drawcall_count++;
}

void ads_process_drawcalls(ads_session_t* session)
{
    for (uint16_t i = 0; i < session->drawcall_count; i++)
    {
        akr_handle_drawcall(&session->calls[i], session->buf, session->temp_buf);
    }
    session->drawcall_count = 0;
}
