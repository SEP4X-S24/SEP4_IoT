#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "dht11.h"
#include "wifi.h"
#include "weather.h"
#include "light.h"
#include <cJSON.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/sleep.h>
#include <stdbool.h>

// Define the connection parameters
#define SSID "Norlys83766"
#define psswd "bas81ymer29"
#define address "20.13.143.114"
#define port 2228

char received_message[128];
bool ping_timeout = false;
int timeout_count = 0;

void init_all()
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
        ping_timeout = false;
        timeout_count = 0;
    }
}

WIFI_ERROR_MESSAGE_t wifi_connect()
{
    wifi_command_join_AP(SSID, psswd);
    return wifi_command_create_TCP_connection(address, port, update_data, received_message);
}

int main()
{
    init_all();
    sei();

    display_setValues(9, 9, 9, 9);

    while (1)
    {
        WIFI_ERROR_MESSAGE_t connection = WIFI_ERROR_NOT_RECEIVING;
        while (connection != WIFI_OK)
        {
            _delay_ms(500);
            display_int(7777);
            connection = wifi_connect();
        }
        display_int(8888);
        ping_timeout = false;
        timeout_count = 0;
        while (!ping_timeout) 
        {
            while (timeout_count < 31) // this is so the updateWeather interrupt resets 31 minute countdown
            {
                _delay_ms(60000);
                timeout_count +=1;
            }
            ping_timeout = true;
        }
        wifi_command_close_TCP_connection();
    }
}
