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

// Define the connection parameters
#define SSID "Como_33?"
#define psswd "Aquilina1"
#define address "20.13.143.114"
#define port 2228

char *received_message;

void init_all_sensors()
{
    wifi_init();
    weather_init();
    display_init();
}

void update_data()
{
    if (strcmp(received_message, "updateWeather") == 0)
    {
        cJSON *json = cJSON_CreateObject();

        TempHumidLight collectedValues = updateWeather();

        // adding the values to the json
        cJSON_AddNumberToObject(json, "temperature", collectedValues.temp);
        cJSON_AddNumberToObject(json, "humidity", collectedValues.humid);
        cJSON_AddNumberToObject(json, "light", collectedValues.light);
        char *jsonString = cJSON_Print(json);
        size_t length = strlen(jsonString);
        wifi_command_TCP_transmit((unsigned char *)jsonString, length);
        cJSON_free(json);
    }
}


void wifi_connect()
{
    wifi_command_join_AP(SSID, psswd);
    wifi_command_create_TCP_connection(address, port, update_data, received_message);
}

int main()
{
    // initialices all the required arduino's sensors
    init_all_sensors();

    display_setValues(9, 9, 9, 9);

    // connects to backend
    wifi_connect();

    display_setValues(0, 0, 0, 0);
}