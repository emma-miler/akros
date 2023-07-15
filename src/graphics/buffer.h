#pragma once

#include "../uefi/uefi.h"
#include "../libs/ssfn.h"
#include "primitives.h"

struct scrbuf_t;
typedef struct {
    efi_gop_t* gop;

    // Buffer properties
    uint64_t size;
    uint64_t width;
    uint64_t height;

    // Data
    uint32_t* data;
    ssfn_buf_t* fontbuffer;
    ssfn_t* ssfn_ctx;
} scrbuf_t;

scrbuf_t* scrbuf_Create(efi_gop_t* gop, ssfn_t* ctx, ssfn_buf_t* buf, uint16_t width, uint16_t height);
void scrbuf_Clear(scrbuf_t* buf);
void scrbuf_Activate(scrbuf_t* buf);
void scrbuf_SetPixel(scrbuf_t* buf, uint16_t x, uint16_t y, uint32_t color);
void scrbuf_DrawText(scrbuf_t* buf, uint16_t x, uint16_t y, char* str);
void scrbuf_DrawTextN(scrbuf_t* buf, uint16_t x, uint16_t y, char* str, uint16_t n);
void scrbuf_DrawRect(scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void scrbuf_DrawBorder(scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void scrbuf_Overlay(scrbuf_t* buf, scrbuf_t* src, uint16_t destX, uint16_t destY);
void scrbuf_Copy(scrbuf_t* buf, scrbuf_t* src, rect_t* mask);
