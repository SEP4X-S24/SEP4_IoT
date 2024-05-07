#include "temperature_humidity.h"
#include "dht11.h"
#include "stdio.h"
#include "stdlib.h"

TempHumid temperature_humidity_get_combined_values()
{
    uint8_t temperature_integer;
    uint8_t temperature_decimal;
    uint8_t humidity_integer;
    uint8_t humidity_decimal;

    if (dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal) == DHT11_OK) {
       
        float combine_temp = temperature_integer + (temperature_decimal / 100.0);
        float combine_humid = humidity_integer + (humidity_decimal/100);

        TempHumid newData;
        newData.temp = combine_temp;
        newData.humid = combine_humid;

        return newData;
    }
    
}
