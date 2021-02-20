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

#include <esp_http_server.h>

#include "esp_log.h"
#include "mqtt_client.h"

#include "error.hpp"
#include "mqtt.hpp"
#include "nvs.hpp"
#include "sys.hpp"
#include "web.hpp"

extern "C" esp_err_t app_connect();

static const char *TAG = "SensorStation";
static int param = 1;

NVS*		nvs = NULL;

void app()
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    esp_log_level_set("*", ESP_LOG_INFO);

    esp_err_t err = nvs_flash_init();
    is_errors(TAG, err, "NVS Flash initialization...");

    err = esp_netif_init();
    is_errors(TAG, err, "NetIF Initialization");

    err = esp_event_loop_create_default();
    is_errors(TAG, err, "Event Loop Creation...");

    err = example_connect();
    is_errors(TAG, err, "Connecting to wifi...");

    // MQTT will register itself on the default event loop and return
    mqtt_app_start(&param);

    // Create the task, storing the handle.  Note that the passed parameter ucParameterToPass
    // must exist for the lifetime of the task, so in this case is declared static.  If it was just an
    // an automatic stack variable it might no longer exist, or at least have been corrupted, by the time
    // the new task attempts to access it.
    // static uint8_t ucParameterToPass;
    // int p = 1;
    // TaskHandle_t http_task_handle = NULL;
    // xTaskCreate(httpd_task, "WEB", 1024, &p, tskIDLE_PRIORITY, &http_task_handle);

    for (;;) {
	printf("tick\n");
	vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main();
void app_main(void)
{
    app();
}
