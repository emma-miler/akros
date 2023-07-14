#pragma once
#include "graphics.h"

akr_scrbuf_t* akr_scrbuf_Create(efi_gop_t* gop, ssfn_t* ctx, ssfn_buf_t* buf, uint16_t width, uint16_t height);
void akr_scrbuf_Clear(akr_scrbuf_t* buf);
void akr_scrbuf_Activate(akr_scrbuf_t* buf);
void akr_scrbuf_SetPixel(akr_scrbuf_t* buf, uint16_t x, uint16_t y, uint32_t color);
void akr_scrbuf_DrawText(akr_scrbuf_t* buf, uint16_t x, uint16_t y, char* str);
void akr_scrbuf_DrawTextN(akr_scrbuf_t* buf, uint16_t x, uint16_t y, char* str, uint16_t n);
void akr_scrbuf_DrawRect(akr_scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void akr_scrbuf_DrawBorder(akr_scrbuf_t* buf, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void akr_scrbuf_Overlay(akr_scrbuf_t* buf, akr_scrbuf_t* src, uint16_t destX, uint16_t destY);
