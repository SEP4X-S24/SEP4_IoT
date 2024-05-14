#include <util/delay.h>
#include <stdlib.h>
#include "display.h"
#include "dht11.h"
#include "wifi.h"
#include "weather.h"
#include "light.h"
#include <cJSON.h>
#include <string.h>

int main()
{
    weather_init();
    display_init();


    while (1)
    {
        display_int(light_read());
        _delay_ms(2000);
    }
    
}