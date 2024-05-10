#include <util/delay.h>
#include <stdlib.h>
#include "display.h"
#include "dht11.h"
#include "wifi.h"
#include "weather.h"
#include "light.h"
#include <cJSON.h>

int main()
{
    wifi_init();
    wifi_command_join_AP("Como_33?", "Aquilina1");
    wifi_command_create_TCP_connection("192.168.1.226", 80, NULL, NULL);
    cJSON *root = cJSON_CreateObject();
    weather_init();
    display_init();
    display_setValues(0,0,0,0);
    float tempHumidLight[] = {0,0,0};
    float tenSeconds = 10000;
    updateWeather(tempHumidLight);
    cJSON_AddNumberToObject(root, "temperature", tempHumidLight[0]);
    cJSON_AddNumberToObject(root, "humidity", tempHumidLight[1]);
    cJSON_AddNumberToObject(root, "light", tempHumidLight[2]);

    char *jsonString = cJSON_Print(root);

    size_t length = strlen(str);


    wifi_command_TCP_transmit(jsonString, length);
    // while (1)
    // {        
    // display_int((int16_t)(tempHumidLight[0]));
    // _delay_ms(tenSeconds);
    // display_int((int16_t)(tempHumidLight[1]));
    // _delay_ms(tenSeconds);
    // display_int((int16_t)(tempHumidLight[2]));
    // _delay_ms(tenSeconds);
    // display_int(9999);
    // _delay_ms(tenSeconds);
        // send tempHumidLight to backend
        // weather.updateWeather(tempHumidLight) updates the three three minute averages
        // this should probably not be in a while(true) loop, but that will be when we figure out connection
    // }
}