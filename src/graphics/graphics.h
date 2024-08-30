#pragma once

#include "uefi/uefi.h"
#include "libs/ssfn.h"

#include "buffer.h"

typedef struct
{
   efi_gop_t* (*GetGop)();
   int (*SetMode)(efi_gop_t* gop);

   akr_scrbuf_singleton_t* Screen;
} akr_graphics_singleton_t;
extern akr_graphics_singleton_t* Graphics;

void akr_init_graphics();
