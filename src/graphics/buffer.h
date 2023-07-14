#pragma once

#include "../uefi/uefi.h"
#include "../libs/ssfn.h"

struct akr_scrbuf_t;
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
} akr_scrbuf_t;

typedef struct
{
    akr_scrbuf_t* (*Create)(efi_gop_t* gop, ssfn_t* ctx, ssfn_buf_t* buf, uint16_t width, uint16_t height);
    void (*Activate)(akr_scrbuf_t* buf);
    void (*Clear)(akr_scrbuf_t* buf);
    void (*SetPixel)(akr_scrbuf_t* buf, uint16_t x, uint16_t y, uint32_t color);
    void (*DrawText)(akr_scrbuf_t* buf, uint16_t x, uint16_t y, char* str);
    void (*DrawTextN)(akr_scrbuf_t* buf, uint16_t x, uint16_t y, char* str, uint16_t n);
    void (*DrawBorder)(akr_scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
    void (*DrawRect)(akr_scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
    void (*Overlay)(akr_scrbuf_t* buf, akr_scrbuf_t* src, uint16_t destX, uint16_t destY);

} akr_scrbuf_singleton_t;
akr_scrbuf_singleton_t* akr_scrbuf_singleton_init();

