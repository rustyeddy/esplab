#pragma once

static const char *TAG = "MQTT_THERMO";

extern void mqtt_app_start();
extern int mqtt_send_temp(float tempf);

