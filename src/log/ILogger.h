#pragma once

class ILogger {
  public:
    virtual void Info(const uchar* msg, ...) = 0;
};