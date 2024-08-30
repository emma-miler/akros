#include "BasicLogger.h"
#include "../clib.h"
#include "../io/ConsoleDevice.h"

BasicLogger::BasicLogger(IOutputDevice& dev) : _sink(dev) {}

void BasicLogger::Info(const uchar* msg, ...)
{
    uchar buf[512];
    va_list args;
    va_start(args, msg);
    vsnprintf(buf, sizeof(buf), msg, args);
    _sink.Write(buf);
    va_end(args);
}