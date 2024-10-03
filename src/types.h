#pragma once

#include "stdint.h"

#define IN
#define OUT
#define OPTIONAL

typedef char16_t uchar;

struct Keycode
{
    uint16_t ScanCode;
    uchar UnicodeChar;
};