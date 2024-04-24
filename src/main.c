#include <util/delay.h>
#include <stdlib.h>
#include "display.h"
#include "dht11.h"
#include "wifi.h"

int main()
{
    // wifi_init();
    // wifi_command_join_AP("cubeco", "arina123");
    // wifi_command_create_TCP_connection("172.20.10.3", 24, NULL, NULL);
    dht11_init();
    display_init();

    while (1)
    {
        uint8_t temperature_integer, temperature_decimal;
        char str[64];
       

        if (dht11_get(NULL, NULL, &temperature_integer, &temperature_decimal) == DHT11_OK)
        {
            display_int(temperature_integer);
            _delay_ms(2000);
        }
    }
}