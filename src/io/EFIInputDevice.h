#pragma once

#include "IInputDevice.h"

class EFIInputDevice : public IInputDevice {
  public:
    virtual int ReadOne(OUT Keycode* keycode);
};