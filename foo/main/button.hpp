#pragma once

#include <iot_button.h>
#include "pin.hpp"

class Button : public Pin
{
protected:
    button_handle_t	_button_handle;

public:
    Button(int p);
};

