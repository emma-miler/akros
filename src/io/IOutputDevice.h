#pragma once
#include "../types.h"

class IOutputDevice {
  public:
    virtual int Write(uchar* message) = 0;
};
