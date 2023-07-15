#pragma once

#include "../uefi/uefi.h"
#include "../libs/ssfn.h"

#include "buffer.h"

efi_gop_t* akr_graphics_GetGop();
int akr_graphics_SetMode(efi_gop_t* gop);
