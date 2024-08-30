#include "IOutputDevice.h"

class ConsoleDevice : public IOutputDevice {
  public:
    ConsoleDevice() {}

    virtual int Write(uint16_t* message);
};
