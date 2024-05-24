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
#define SSID "Pixel de Hugo"
#define psswd "Lumia535"
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

void create_and_send_weather()
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
        display_int(5555);
}

void update_data()
{
    if (strcmp(received_message, "updateWeather") == 0)
    {
        create_and_send_weather();
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
            display_int(7777);
            connection = wifi_connect();
            _delay_ms(2000);
        }
        create_and_send_weather();
        display_int(4444);
        ping_timeout = false;
        timeout_count = 0;
        while (!ping_timeout) 
        {
            while (timeout_count < 301) // this is so the updateWeather interrupt resets 30 minute countdown
            {
                display_int(timeout_count);
                _delay_ms(6000);
                timeout_count +=1;
            }
            ping_timeout = true;
        }
        display_int(6666);
        wifi_command_close_TCP_connection();
    }
}
