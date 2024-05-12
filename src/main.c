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
    wifi_init();
    wifi_command_join_AP("Norlys83766", "bas81ymer29");
    wifi_command_create_TCP_connection("192.168.87.126",88, NULL, NULL);
    cJSON *root = cJSON_CreateObject();
    weather_init();
    display_init();
    display_setValues(0, 0, 0, 0);
    TempHumidLight collectedValues = updateWeather();
    cJSON_AddNumberToObject(root, "temperature", collectedValues.temp);
    cJSON_AddNumberToObject(root, "humidity", collectedValues.humid);
    cJSON_AddNumberToObject(root, "light", collectedValues.light);
    char *jsonString = cJSON_Print(root);
    size_t length = strlen(jsonString);
    wifi_command_TCP_transmit((unsigned char*)jsonString, length);
    display_int(9999);

    while (1)
    {
        display_int(collectedValues.temp);
        _delay_ms(1000);
        display_int(collectedValues.humid);
        _delay_ms(1000);
        display_int(collectedValues.light);
        _delay_ms(1000);
        display_int(9999);
        _delay_ms(1000);
    }
    
}