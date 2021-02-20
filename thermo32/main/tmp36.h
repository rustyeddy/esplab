#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_adc_cal.h"
#include "esp_log.h"

typedef struct tmp36_ {
    adc_channel_t	tmp36_channel;
    adc_unit_t		tmp36_unit;
    adc_atten_t		tmp36_atten;
    int			tmp36_delay;
    int			tmp36_vref;
    int			tmp36_samples;

    esp_adc_cal_characteristics_t *tmp36_adc_chars;
} tmp36_t;
    
extern tmp36_t*	tmp36_new(adc_channel_t chan, adc_unit_t u);
extern float	tmp36_read(tmp36_t *tmp);
