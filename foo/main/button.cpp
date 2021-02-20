#include "app.hpp"

#include "pin.hpp"
#include JUMPSTART_BOARD

#include "button.hpp"
#include "relay.hpp"

void button_push_cb(void *arg)
{
    relay->toggle();
}

Button::Button(int p) : Pin(p, INPUT)
{
    // configure_push_button
    _button_handle = iot_button_create(JUMPSTART_BOARD_BUTTON_GPIO,
				       (button_active_t) JUMPSTART_BOARD_BUTTON_ACTIVE_LEVEL);
    if (_button_handle) {
	char *str = (char *)"RELEASE";
        iot_button_set_evt_cb(_button_handle, BUTTON_CB_RELEASE, button_push_cb,
			      str);
    }
}
