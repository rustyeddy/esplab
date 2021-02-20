#include <stdio.h>

#include "esp_system.h"

#include "sys.hpp"

void reboot()
{
    printf("Rebooting ... \n");
    fflush(stdout);
    esp_restart();
}
