/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "app.hpp"
#include JUMPSTART_BOARD

#include "pin.hpp"
#include "button.hpp"
#include "relay.hpp"

Button*		button = NULL;
Relay*		relay = NULL;

void app()
{

    button = new Button(JUMPSTART_BOARD_BUTTON_GPIO);
    assert(button);

    relay = new Relay(JUMPSTART_BOARD_OUTPUT_GPIO);
    assert(relay);

    int i = 0;
    app_driver_init();
    while (1) {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

extern "C" {
    void app_main()
    {
	app();
    }
}
