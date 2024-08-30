#include "buffer.h"
#include "../libs/ssfn.h"

#include "../macros.h"
#include "graphics.h"

scrbuf_t* scrbuf_Create(efi_gop_t* gop, ssfn_t* ctx, ssfn_buf_t* buf, uint16_t width, uint16_t height)
{
    scrbuf_t* buffer = malloc(sizeof(scrbuf_t)); // Allocate struct
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

    scrbuf_Clear(buffer);

    return buffer;
}

void scrbuf_Clear(scrbuf_t* buf)
{
    memset(buf->data, 0, buf->size);
}

void scrbuf_Activate(scrbuf_t* buf)
{
    buf->gop->Blt(buf->gop, buf->data, EfiBltBufferToVideo, 0, 0, 0, 0, buf->width, buf->height, 0);
}

void scrbuf_SetPixel(scrbuf_t* buf, uint16_t x, uint16_t y, uint32_t color)
{
    buf->data[(y * buf->width) + x] = color;
}

void scrbuf_DrawText(scrbuf_t* buf, uint16_t x, uint16_t y, char* str)
{
    int ret;
    buf->fontbuffer->x = x;
    buf->fontbuffer->y = y;
    while((ret = ssfn_render(buf->ssfn_ctx, buf->fontbuffer, str)) > 0)
        str += ret;
}

void scrbuf_DrawTextN(scrbuf_t* buf, uint16_t x, uint16_t y, char* str, uint16_t n)
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

void scrbuf_DrawRect(scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    for (int x = x1; x < x2; x++)
    {
        for (int y = y1; y < y2; y++)
        {
            scrbuf_SetPixel(buf, x, y, color);
        }
    }
}

void scrbuf_DrawBorder(scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    for (int x = x1; x < x2; x++)
    {
        scrbuf_SetPixel(buf, x, y1, color);
        scrbuf_SetPixel(buf, x, y2 - 1, color);
    }
    for (int y = y1; y < y2; y++)
    {
        scrbuf_SetPixel(buf, x1, y, color);
        scrbuf_SetPixel(buf, x2 - 1, y, color);
    }
}


void scrbuf_Overlay(scrbuf_t* buf, scrbuf_t* src, uint16_t destX, uint16_t destY)
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
void scrbuf_Copy(scrbuf_t* buf, scrbuf_t* src, rect_t* mask)
{
    for (int y = mask->y; y < mask->height + mask->y; y++)
    {
        for (int x = mask->x; x < mask->width + mask->x; x++)
        {
            buf->data[(y * buf->width) + x] = src->data[(y * src->width) + x];
        }
        //memcpy(&buf->data[y*src->height + (int)mask->x], &src->data[y*src->height + (int)mask->x], mask->width * sizeof(uint32_t));
    }
}
