#pragma once

#include "IOutputDevice.h"

class EFIOutputDevice : public IOutputDevice {
  public:
    virtual int Write(const uchar* message);
    virtual void ClearScreen();
    virtual void ClearLine();
};