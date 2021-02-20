#pragma once

#include <esp_err.h>
#include <esp_log.h>

#include <string>

bool is_ok(const char *tag, esp_err_t err);
bool is_error(const char *tag, esp_err_t err);
bool is_errors(const char *tag, esp_err_t err, std::string str);
