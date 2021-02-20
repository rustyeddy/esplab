#pragma once

#include <string>

#include <esp_err.h>
#include <nvs_flash.h>

using namespace std;

class NVS
{
private:
    string		_name;
    nvs_handle_t	_nvs_handle	= -1;
    esp_err_t		_err		= ESP_OK;

public:
    NVS(string name);

    esp_err_t	init();
    esp_err_t	open();
    bool	is_open();
    void	close();

    int		increment(string key);
    esp_err_t	read(string key, int* val);
    esp_err_t	write(string key, int val);

    esp_err_t	get_error() { return _err; }
};

extern NVS* nvs;
