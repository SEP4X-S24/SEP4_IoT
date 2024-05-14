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
#include <az_iot_hub_client.h>
#include <az_result.h>
#include <az_span.h>

static const char *connectionString = "HostName=weatherstation.azure-devices.net;DeviceId=weather-arduino;SharedAccessKey=wWZRLEYdHXcS/JMjykNYuQjEfd55nwUciAIoTGZ5ty8=";

int main()
{
    wifi_init();
    wifi_command_join_AP("Pixel de Hugo", "Lumia535");
    //wifi_command_create_TCP_connection("192.168.87.126", 80, NULL, NULL);
    az_iot_hub_client client;
    az_iot_hub_client_options options = az_iot_hub_client_options_default();

    az_span device_id = az_span_create_from_str("weather-arduino");
    az_result result = az_iot_hub_client_init(&client, az_span_create_from_str(connectionString), device_id, &options);
    if (az_result_failed(result))
    {
        printf("Failed to initialize client, az_result return code %04x\n", result);
    }

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
    result = az_log_set_message_callback(&client, az_span_create_from_str(jsonString), NULL);
    if (az_result_failed(result))
    {
        printf("Failed to send message, az_result return code %04x\n", result);
    }

    delay(10000);

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