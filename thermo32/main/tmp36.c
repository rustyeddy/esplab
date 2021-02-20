#include "tmp36.h"

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

static void check_efuse()
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

// tmp36_new Creates a new analog channel from the given channel and unit
// memory is allocated from heap, the user is responsible for disposing
// of it or call tmp36_dispose().
tmp36_t* tmp36_new(adc_channel_t c, adc_unit_t u)
{
    tmp36_t *t = calloc(1, sizeof(tmp36_t));
    assert(t);

    t->tmp36_channel	= c;			// e.g. ADC_CHANNEL_5
    t->tmp36_unit	= u;			// e.g. ADC_UNIT_1
    t->tmp36_atten	= ADC_ATTEN_DB_0;
    t->tmp36_vref	= 1100;

    t->tmp36_delay	= 5000;	/* 5 seconds */
    t->tmp36_samples	= 64;

    check_efuse();
    if (t->tmp36_unit == ADC_UNIT_1) {
	adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten((adc1_channel_t)t->tmp36_channel, t->tmp36_atten);
    } else {
	adc2_config_channel_atten((adc2_channel_t)t->tmp36_channel, t->tmp36_atten);
    }
    t->tmp36_adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(t->tmp36_unit, t->tmp36_atten,
							    ADC_WIDTH_BIT_12,
							    t->tmp36_vref, t->tmp36_adc_chars);
    print_char_val_type(val_type);
    return t;
}

void tmp36_dispose(tmp36_t *t) {
    // XXX Sould be sure to shutdown ...
    free(t);
}

/*
 * tmp36_read() takes an averaged sampling of measurements to smooth
 * out anamolies in voltage.
 */
float tmp36_read(tmp36_t *t)
{
    uint32_t adc_reading = 0;
    for (int i = 0; i < t->tmp36_samples; i++) {
	if (t->tmp36_unit == ADC_UNIT_1) {
	    adc_reading += adc1_get_raw((adc1_channel_t)t->tmp36_channel);
	} else {
	    int raw;
	    adc2_get_raw((adc2_channel_t) t->tmp36_channel, ADC_WIDTH_BIT_12, &raw);
	    adc_reading += raw;
        }
    }
    adc_reading /= t->tmp36_samples;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, t->tmp36_adc_chars);
    float temp = (float) voltage / 1023.0;
    return temp * 100;
}

