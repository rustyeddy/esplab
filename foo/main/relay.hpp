#pragma once

#include "pin.hpp"
#include "relay.hpp"

class Relay : public Pin
{
public:
    Relay(int p) : Pin(p, OUTPUT) {}
};

