#include <string>

#include <esp_err.h>
#include <esp_log.h>
#include <nvs_flash.h>

#include "nvs.hpp"

using namespace std;

static const char *TAG = "NVS";

NVS::NVS(string name)
{
    _name = name;
    _err = ESP_OK;
    init();
}

esp_err_t NVS::init()
{
    _err = nvs_flash_init();
    if (_err == ESP_ERR_NVS_NO_FREE_PAGES || _err == ESP_ERR_NVS_NEW_VERSION_FOUND) {

	// NVS partition was truncated and needs to be erased
	// Retry nvs_flash_init
	ESP_LOGW(TAG, "NVS partition was truncated and will be erased.");
	_err = nvs_flash_erase();
	if (_err != ESP_OK) {
	    ESP_LOGE(TAG, "NVS failed while erasing flash: %s\n", esp_err_to_name(_err));
	    return _err;
	}

	_err = nvs_flash_init();
	if (_err != ESP_OK) {
	    ESP_LOGE(TAG, "NVS flash init: %s\n", esp_err_to_name(_err));
	    return _err;
	}
    }
    return _err;
}

esp_err_t NVS::open()
{
    if (_err != ESP_OK) {
	return _err;
    }

    _err = nvs_open(_name.c_str(), NVS_READWRITE, &_nvs_handle);
    if (_err != ESP_OK) {
	ESP_LOGE(TAG, "FAILED to open flash: %s\n", _name.c_str());
	return _err;
    }

    if (_nvs_handle == -1) {
	return -1;
    }
    return ESP_OK;
}

void NVS::close()
{
    nvs_close(_nvs_handle);
    _nvs_handle = -1;
}

esp_err_t NVS::read(string key, int32_t* val)
{
    if (open() != ESP_OK) return _err;

    _err = nvs_get_i32(_nvs_handle, key.c_str(), val);
    switch (_err) {
    case ESP_OK:
	ESP_LOGI(TAG, "NVS::read %s = %d", key.c_str(), *val);
	break;

    case ESP_ERR_NVS_NOT_FOUND:
	ESP_LOGE(TAG, "NVS::read %s not initialized yet.", key.c_str());
	break;

    default:
	ESP_LOGE(TAG, "NVS::read Error (%s) reading!", esp_err_to_name(_err));
	break;
    }

    close();
    return _err;
}

esp_err_t NVS::write(string key, int val)
{
    if (open() != ESP_OK) return _err;

    _err = nvs_set_i32(_nvs_handle, key.c_str(), val);
    if (ESP_OK != _err) {
	ESP_LOGE(TAG, "NVS Counter Write Failed!");
	goto done;
    }

    // Commit written value.  After setting any values, nvs_commit()
    // must be called to ensure changes are written to flash
    // storage. Implementations may write to storage at other times,
    // but this is not guaranteed.
    _err = nvs_commit(_nvs_handle);
    if (ESP_OK != _err) {
	ESP_LOGE(TAG, "NVS Counter Commit Failed!");
	goto done;
    }
    ESP_LOGI(TAG, "NVS Counter Commit Done!");

  done:
    close();
    return _err;
}

int NVS::increment(string key)
{
    _err = open();
    if (_err != ESP_OK) {
	ESP_LOGE(TAG, "Failed to open Non-Volatile Storage: %s\n", esp_err_to_name(_err));
	return _err;
    }

    int counter = 0;
    if (read(key, &counter) != ESP_OK) {
	ESP_LOGE(TAG, "Failed to read NVS: %s\n", esp_err_to_name(_err));
	return _err;
    }
    counter++;
    if (write(key, counter) != ESP_OK) {
	ESP_LOGE(TAG, "Failed to write NVS: %s\n", esp_err_to_name(_err));
	return _err;
    }
    ESP_LOGI(TAG, "Updated restart counter %d ... ", counter);
    return _err;
}

