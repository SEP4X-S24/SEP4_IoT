#include <util/delay.h>
#include <stdio.h>
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
    wifi_command_join_AP("Como_33?", "Aquilina1");
    wifi_command_create_TCP_connection("https://weatherstation4dev.azurewebsites.net", 443, NULL, NULL);
    wifi_command_TCP_transmit("")

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
    wifi_command_TCP_transmit((unsigned char *)jsonString, length);
    display_int(9999);

    _delay_ms(10000);

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