#pragma once
#include <stdint.h>

typedef struct{
    uint8_t temp;
    uint8_t humid;

} TempHumid;

TempHumid temperature_humidity_get_combined_values();
