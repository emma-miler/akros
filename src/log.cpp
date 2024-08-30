#include "log.h"

#include "clib.h"
#include "efi.h"

void debug(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* out, const char* fmt, va_list args)
{
    uint16_t msg[512];

    vsnprintf(msg, sizeof(msg), fmt, args);
    out->OutputString(out, msg);
}

void info(EFI_SYSTEM_TABLE* system, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    debug(system->ConOut, fmt, args);
    va_end(args);
}

void err(EFI_SYSTEM_TABLE* system, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    debug(system->StdErr, fmt, args);
    va_end(args);
}

void log_panic(EFI_SYSTEM_TABLE* system, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    debug(system->StdErr, fmt, args);
    va_end(args);

    while (1) {
    }
}
