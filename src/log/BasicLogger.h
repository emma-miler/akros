#pragma once

#include "../io/IOutputDevice.h"
#include "../types.h"
#include "ILogger.h"

class BasicLogger : public ILogger {
  public:
    BasicLogger(IOutputDevice& dev);
    virtual void Info(const char* msg, ...);

  private:
    IOutputDevice& _sink;
};