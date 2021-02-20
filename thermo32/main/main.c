/* MQTT (over TCP) Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "app.h"
#include "tmp36.h"
#include "pin.h"
#include "oled.h"

static void init(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* 
     * This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
    //mqtt_app_start();
}

// tmp36_task_loop is the task that loops forever.
static void tmp36_task_loop(void *args)
{
    pin_t *red = get_pin(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    assert(red);

    tmp36_t *tmp = tmp36_new(ADC_CHANNEL_6, ADC_UNIT_1);
    assert(tmp);

    while (1) {
	// read the temprature and blink the light while doing so...
	on(red);
	float tempf = tmp36_read(tmp);
	int err = mqtt_send_temp(tempf);
	if (err < 0) {
	    printf("\terror sending temprature over mqtt\n");
	} else {
	    off(red); // red light stays on incase of an error
	}
	vTaskDelay(tmp->tmp36_delay / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    // init will get every thing ready right after boot before we enter
    // into full fledge app mode!
    init();

    xTaskCreate(tmp36_task_loop, "tmp36-loop", 1024 * 2, (void *)0, 10, NULL);
    xTaskCreate(mqtt_app_start, "mqtt-listener", 1024 * 2, (void *)0 , 10, NULL);
}


