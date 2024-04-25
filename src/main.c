#include "wifi.h"
#include <util/delay.h>
#include <stdlib.h>
#include "dht11.h"
#include "display.h"
#include "light.h"

int main()
{
    wifi_init();
    wifi_command_join_AP("Fibernet-IA02414921", "i9T0m716");
    wifi_command_create_TCP_connection("192.168.1.226", 23, NULL, NULL);
    dht11_init();
    display_init();
    light_init();
    while (1)
    {
        uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;
        uint16_t light_value;
        char str[64];
        if (dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal) == DHT11_OK)
        {
            display_int(humidity_integer);
            _delay_ms(2000);

            
        }

        light_value = light_read();
            display_int(light_value);  // Display the light value
            _delay_ms(2000);  

        
    }
}