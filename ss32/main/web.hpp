#pragma once

#include <esp_http_server.h>

extern httpd_handle_t *server;
extern void httpd_task(void *param);
