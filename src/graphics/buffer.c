#include "buffer.h"
#include "../libs/ssfn.h"

#include "../macros.h"
#include "graphics.h"
#include "impl_buffer.h"

akr_scrbuf_t* akr_scrbuf_Create(efi_gop_t* gop, ssfn_t* ctx, ssfn_buf_t* buf, uint16_t width, uint16_t height)
{
    akr_scrbuf_t* buffer = malloc(sizeof(akr_scrbuf_t)); // Allocate struct
    //buffer->size = gop->Mode->FrameBufferSize;
    buffer->size = sizeof(uint32_t) * width * height;
    buffer->data = malloc(buffer->size); // Allocate buffer based on framebuffer size
    buffer->gop = gop;
    buffer->width = width; // Set width
    buffer->height = height; // Set height

    buffer->ssfn_ctx = ctx;
    buffer->fontbuffer = buf;
    buffer->fontbuffer->ptr = (unsigned char*)buffer->data;
    buffer->fontbuffer->w = buffer->width;
    buffer->fontbuffer->h = buffer->height;
    buffer->fontbuffer->p = sizeof(unsigned int) * gop->Mode->Information->PixelsPerScanLine;
    buffer->fontbuffer->fg = 0xFFFFFFFF;
    buffer->fontbuffer->bg = 0x00000000;

    akr_scrbuf_Clear(buffer);

    return buffer;
}

void akr_scrbuf_Clear(akr_scrbuf_t* buf)
{
    memset(buf->data, 0, buf->size);
}

void akr_scrbuf_Activate(akr_scrbuf_t* buf)
{
    buf->gop->Blt(buf->gop, buf->data, EfiBltBufferToVideo, 0, 0, 0, 0, buf->width, buf->height, 0);
}

void akr_scrbuf_SetPixel(akr_scrbuf_t* buf, uint16_t x, uint16_t y, uint32_t color)
{
    buf->data[(y * buf->width) + x] = color;
}

void akr_scrbuf_DrawText(akr_scrbuf_t* buf, uint16_t x, uint16_t y, char* str)
{
    int ret;
    buf->fontbuffer->x = x;
    buf->fontbuffer->y = y;
    while((ret = ssfn_render(buf->ssfn_ctx, buf->fontbuffer, str)) > 0)
        str += ret;
}

void akr_scrbuf_DrawTextN(akr_scrbuf_t* buf, uint16_t x, uint16_t y, char* str, uint16_t n)
{
    int ret;
    buf->fontbuffer->x = x;
    buf->fontbuffer->y = y;
    int i = 0;
    while((ret = ssfn_render(buf->ssfn_ctx, buf->fontbuffer, str)) > 0 && i < n)
    {
        i++;
        str += ret;
    }
}

void akr_scrbuf_DrawRect(akr_scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    for (int x = x1; x < x2; x++)
    {
        for (int y = y1; y < y2; y++)
        {
            akr_scrbuf_SetPixel(buf, x, y, color);
        }
    }
}

void akr_scrbuf_DrawBorder(akr_scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    for (int x = x1; x < x2; x++)
    {
        akr_scrbuf_SetPixel(buf, x, y1, color);
        akr_scrbuf_SetPixel(buf, x, y2 - 1, color);
    }
    for (int y = y1; y < y2; y++)
    {
        akr_scrbuf_SetPixel(buf, x1, y, color);
        akr_scrbuf_SetPixel(buf, x2 - 1, y, color);
    }
}


void akr_scrbuf_Overlay(akr_scrbuf_t* buf, akr_scrbuf_t* src, uint16_t destX, uint16_t destY)
{
    for (int x = 0; x < src->width; x++)
    {
        for (int y = 0; y < src->height; y++)
        {
            // uint32_t srcIndex = (y * src->width) + x;
            if (src->data[(y * src->width) + x] >> 24)
            {
                buf->data[((y+destY) * buf->width) + x + destX] = src->data[(y * src->width) + x];
            }
        }
    }
}

akr_scrbuf_singleton_t* akr_scrbuf_singleton_init()
{
    akr_scrbuf_singleton_t* scrbuf = malloc(sizeof(akr_scrbuf_singleton_t));
    IMPL(akr, scrbuf, Create);
    IMPL(akr, scrbuf, Clear);
    IMPL(akr, scrbuf, Activate);
    IMPL(akr, scrbuf, SetPixel);
    IMPL(akr, scrbuf, DrawText);
    IMPL(akr, scrbuf, DrawTextN);
    IMPL(akr, scrbuf, DrawRect);
    IMPL(akr, scrbuf, DrawBorder);
    IMPL(akr, scrbuf, Overlay);
    return scrbuf;
}
