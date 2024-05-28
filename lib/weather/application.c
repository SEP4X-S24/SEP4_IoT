#ifdef MAIN
#include "application.h"

#define SSID "Pixel de Hugo"
#define psswd "Lumia535"
#define address "20.13.143.114"
#define port 2228

#define BLOCK_SIZE 16

bool ping_timeout = false;
int timeout_count = 0;
struct AES_ctx my_AES_ctx;
bool UnlockingApproved = false;
char received_message[128];
uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

void init_all()
{
    wifi_init();
    weather_init();
    display_init();
    AES_init_ctx(&my_AES_ctx, key);
}

// implementation of PKCS#7 padding
void pad_input(uint8_t *input, size_t *length)
{
    size_t padding_needed = BLOCK_SIZE - (*length % BLOCK_SIZE);
    size_t padded_length = *length + padding_needed;

    for (size_t i = *length; i < padded_length; i++) {
        input[i] = (uint8_t)padding_needed;
    }
    *length = padded_length;
}


void AES_ECB_encrypt_buffer(struct AES_ctx *ctx, uint8_t *buf, size_t length)
{
    for (size_t i = 0; i < length; i += BLOCK_SIZE)
    {
        AES_ECB_encrypt(ctx, buf + i);
    }
}


void bin2hex(const uint8_t *bin, size_t len, char *hex) {
    for (size_t i = 0; i < len; i++) {
        sprintf(hex + (i * 2), "%02x", bin[i]);
    }
    hex[len * 2] = '\0'; // null-terminate 
}

void create_and_send_weather()
{
    cJSON *json = cJSON_CreateObject();

    TempHumidLight collectedValues = updateWeather();

        cJSON_AddNumberToObject(json, "temperature", collectedValues.temp);
        cJSON_AddNumberToObject(json, "humidity", collectedValues.humid);
        cJSON_AddNumberToObject(json, "light", collectedValues.light);
        char *jsonString = cJSON_Print(json);
        size_t length = strlen(jsonString);
    
        pad_input((uint8_t *)jsonString, &length);

        char hex[length * 2 + 1]; // Adjust the size of hex array to accommodate null-terminated string

        AES_ECB_encrypt_buffer(&my_AES_ctx, (uint8_t *)jsonString, length);
        
        bin2hex((uint8_t *)jsonString, length, hex);

        // Prepend "ENCRYPTED:" to the hex string
        const char *prefix = "ENCRYPTED:";
        size_t prefixLength = strlen(prefix);
        size_t totalLength = prefixLength + strlen(hex);
        char *finalData = (char *)malloc(totalLength + 1);  // +1 for null-termination
        strcpy(finalData, prefix);
        strcat(finalData, hex);

        // Transmit the final data
        wifi_command_TCP_transmit((unsigned char *)finalData, totalLength);

        // Clean up
        cJSON_Delete(json);
        free(jsonString);
        free(finalData);

        ping_timeout = false;
        timeout_count = 0;
    
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

void app_start()
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
#endif