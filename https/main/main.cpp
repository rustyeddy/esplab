#include "app.hpp"

extern "C" void app_main(int argc, char **argv)
{
    // Get wifi connected 
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Starts an event loop and thread
    wss_main();
}
