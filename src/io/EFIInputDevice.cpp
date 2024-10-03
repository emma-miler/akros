#include "EFIInputDevice.h"
#include "../efi.h"

int EFIInputDevice::ReadOne(OUT Keycode* keycode)
{
    UINTN idx;
    g_EfiSystemTable->BootServices->WaitForEvent(1, &g_EfiSystemTable->ConIn->WaitForKey, &idx);
    EFI_STATUS status = g_EfiSystemTable->ConIn->ReadKeyStroke(g_EfiSystemTable->ConIn, (EFI_INPUT_KEY*)keycode);
    if (status == EFI_NOT_READY)
        return -1;

    return keycode->ScanCode;
}