#ifdef TEMP_HUMID
#include "temperature_humidity.h"
#include "dht11.h"
#include "stdio.h"
#include "stdlib.h"
#include "display.h"

#ifdef WINDOWS_TEST
#else
#include <util/delay.h>
#endif


TempHumid temperature_humidity_get_combined_values()
{
    uint8_t temperature_integer;
    uint8_t temperature_decimal;
    uint8_t humidity_integer;
    uint8_t humidity_decimal;

    if (dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal) == DHT11_OK) {

        TempHumid newData;
        newData.temp = temperature_integer;
        newData.humid = humidity_integer;

        return newData;
    }
    else
    {
        display_int(7777);
        _delay_ms(1000);
    }
    TempHumid fail;
    return fail;
}
#endif