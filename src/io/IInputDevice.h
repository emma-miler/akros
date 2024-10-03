#pragma once
#include "../types.h"

class IInputDevice {
  public:
    virtual int ReadOne(OUT Keycode* keycode) = 0;
};
