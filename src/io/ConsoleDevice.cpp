#include "ConsoleDevice.h"
#include "../clib.h"
#include "../efi.h"
#include "../log.h"

int ConsoleDevice::Write(uint16_t* message)
{
    g_EfiSystemTable->ConOut->OutputString(g_EfiSystemTable->ConOut, message);
    return 0;
}