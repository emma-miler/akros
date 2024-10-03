#include "ConsoleDevice.h"
#include "../clib.h"
#include "../efi.h"
#include "../log.h"

int ConsoleDevice::Write(const uchar* message) { return _out.Write(message); }

int ConsoleDevice::ReadOne(OUT Keycode* keycode) { return _in.ReadOne(keycode); }

void ConsoleDevice::ClearScreen() { return _out.ClearScreen(); }
void ConsoleDevice::ClearLine() { return _out.ClearLine(); }