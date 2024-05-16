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

//Define the connection parameters
#define SSID "Como_33?"
#define psswd "Aquilina1"
#define address "20.13.143.114"
#define port 2228

void init_all_sensors()
{
    wifi_init();
    weather_init();
    display_init();
}

void wifi_connect()
{
    wifi_command_join_AP(SSID, psswd);
    wifi_command_create_TCP_connection(address, port, NULL, NULL);
}

void send_data()
{
    cJSON *json = cJSON_CreateObject();

    TempHumidLight collectedValues = updateWeather();

    //adding the values to the json
    cJSON_AddNumberToObject(json, "temperature", collectedValues.temp);
    cJSON_AddNumberToObject(json, "humidity", collectedValues.humid);
    cJSON_AddNumberToObject(json, "light", collectedValues.light);
    char *jsonString = cJSON_Print(json);
    size_t length = strlen(jsonString);
    wifi_command_TCP_transmit((unsigned char *)jsonString, length);
    cJSON_free(json);
}


int main()
{  
    //initialices all the required arduino's sensors
    init_all_sensors();

    //connects to backend
    wifi_connect();

    //init json object

    display_setValues(0, 0, 0, 0);

    while (1)
    {
        char* response;  
        //listen for incoming connection
        if (strcmp(response, "update_weather") == 0 )
        {
            send_data();
        }
        //handle other actions?

    }
}