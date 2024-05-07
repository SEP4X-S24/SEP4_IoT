
#pragma once
#include <stdint.h>

typedef struct{
    float temp;
    float humid;

} TempHumid;

TempHumid temperature_humidity_get_combined_values();
