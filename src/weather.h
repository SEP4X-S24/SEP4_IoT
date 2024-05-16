#pragma once
#include <stdint.h>
typedef struct{
    uint8_t temp;
    uint8_t humid;
    uint8_t light;

} TempHumidLight; 

void weather_init();
TempHumidLight updateWeather();