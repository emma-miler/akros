#pragma once

#include "../../io/ConsoleDevice.h"

class ShellInstance 
{

public:
    ShellInstance(ConsoleDevice& con) : _con(con) {};

    void Start();

private:
    ConsoleDevice& _con;

};