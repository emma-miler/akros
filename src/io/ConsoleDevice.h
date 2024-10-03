#pragma once

#include "EFIInputDevice.h"
#include "EFIOutputDevice.h"

class ConsoleDevice : public IOutputDevice {

  private:
    IOutputDevice& _out;
    IInputDevice& _in;

  public:
    ConsoleDevice(IOutputDevice& out, IInputDevice& in) : _out(out), _in(in) {}

    virtual int Write(const uchar* message);
    virtual int ReadOne(OUT Keycode* keycode);
    virtual void ClearScreen();
    virtual void ClearLine();
};
