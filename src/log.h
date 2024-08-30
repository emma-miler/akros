#pragma once
#include "clib.h"
#include "efi.h"
void debug(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* out, const char* fmt, va_list args);
void info(EFI_SYSTEM_TABLE* system, const char* fmt, ...);
void err(EFI_SYSTEM_TABLE* system, const char* fmt, ...);
void log_panic(EFI_SYSTEM_TABLE* system, const char* fmt, ...);
