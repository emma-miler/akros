#pragma once

class ILogger {
  public:
    virtual void Info(const char* msg, ...) = 0;
};