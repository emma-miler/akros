#include "EFIOutputDevice.h"
#include "../efi.h"

int EFIOutputDevice::Write(const uchar* message) { return g_EfiSystemTable->ConOut->OutputString(g_EfiSystemTable->ConOut, message); }

void EFIOutputDevice::ClearLine()
{
    UINTN curRow = g_EfiSystemTable->ConOut->Mode->CursorRow;
    UINTN maxRow, maxCol;
    g_EfiSystemTable->ConOut->QueryMode(g_EfiSystemTable->ConOut, g_EfiSystemTable->ConOut->Mode->Mode, &maxRow, &maxCol);
    g_EfiSystemTable->ConOut->SetCursorPosition(g_EfiSystemTable->ConOut, 0, curRow);
    for (int i = 0; i < maxCol; i++) {
        g_EfiSystemTable->ConOut->OutputString(g_EfiSystemTable->ConOut, u" ");
    }
    g_EfiSystemTable->ConOut->SetCursorPosition(g_EfiSystemTable->ConOut, 0, curRow);
}

void EFIOutputDevice::ClearScreen() { g_EfiSystemTable->ConOut->ClearScreen(g_EfiSystemTable->ConOut); }