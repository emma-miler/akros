#pragma once
#include "../types.h"

class IOutputDevice {
  public:
    virtual int Write(const uchar* message) = 0;
    virtual void ClearScreen() = 0;
    virtual void ClearLine() = 0;
};
