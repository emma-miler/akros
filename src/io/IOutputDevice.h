#pragma once
#include "../types.h"

class IOutputDevice {
  public:
    virtual int Write(uint16_t* message) = 0;
};
