#pragma once

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

typedef struct oled_ {
    uint8_t oled_addr;
} oled_t;
