/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#pragma once

#include "button.hpp"
#include "relay.hpp"

void app_driver_init(void);
int app_driver_set_state(bool state);
bool app_driver_get_state(void);

extern Button *button;
extern Relay  *relay;
