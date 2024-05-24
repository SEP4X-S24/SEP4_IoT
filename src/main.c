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
#include <aes.h>

// Define the connection parameters
#define SSID "Pixel de Hugo"
#define psswd "Lumia535"
#define address "192.168.114.113"
#define port 88

#define BLOCK_SIZE 16

bool ping_timeout = false;
int timeout_count = 0;
struct AES_ctx my_AES_ctx;
bool UnlockingApproved = false;
char received_message[128];
uint8_t key[] = "5468617473206D79204B756E67204675";

void init_all()
{
    wifi_init();
    weather_init();
    display_init();
    AES_init_ctx(&my_AES_ctx, key);
}

// Function to pad the input to a multiple of the block size
void pad_input(uint8_t *input, size_t *length)
{
    size_t padded_length = (*length + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);
    memset(input + *length, 0, padded_length - *length);
    *length = padded_length;
}

void AES_ECB_encrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length)
{
    for (size_t i = 0; i < length; i += BLOCK_SIZE)
    {
        AES_ECB_encrypt(ctx, buf + i);
    }
}

void AES_ECB_decrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length)
{
    for (size_t i = 0; i < length; i += BLOCK_SIZE)
    {
        AES_ECB_decrypt(ctx, buf + i);
    }
}

void update_data()
{
    if (strcmp(received_message, "updateWeather") == 0)
    {
        cJSON *json = cJSON_CreateObject();

        TempHumidLight collectedValues = updateWeather();


        cJSON_AddNumberToObject(json, "temperature", collectedValues.temp);
        cJSON_AddNumberToObject(json, "humidity", collectedValues.humid);
        cJSON_AddNumberToObject(json, "light", collectedValues.light);
        char *jsonString = cJSON_Print(json);
        size_t length = strlen(jsonString);


        pad_input((uint8_t *)jsonString, &length);


        AES_ECB_encrypt_buffer(&my_AES_ctx, (uint8_t *)jsonString, length);

        wifi_command_TCP_transmit((unsigned char *)jsonString, length);

        AES_ECB_decrypt_buffer(&my_AES_ctx, (uint8_t *)jsonString, length);

        cJSON_Delete(json);
        free(jsonString);

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
        while (!ping_timeout)
        {
            while (timeout_count < 31) // this is so the updateWeather interrupt resets 31 minute countdown
            {
                _delay_ms(60000);
                timeout_count += 1;
            }
            ping_timeout = true;
        }
        wifi_command_close_TCP_connection();
    }
}
