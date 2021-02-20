#include "error.hpp"

bool is_error(const char *tag, esp_err_t err)
{
    if (err != ESP_OK) {
	ESP_LOGE(tag, "[%d] %s\n", err, esp_err_to_name(err));
    }
    return false;
}

bool is_errors(const char *tag, esp_err_t err, std::string str)
{
    if (err != ESP_OK) {
	ESP_LOGE(tag, "[%d] %s ~ %s\n", err, esp_err_to_name(err), str.c_str());
	return true;
    }
    return false;
}

bool is_ok(const char *tag, esp_err_t err)
{
    
    if (err != ESP_OK) {
	ESP_LOGE(tag, "[%d] %s\n", err, esp_err_to_name(err));
    }
    return false;
}
