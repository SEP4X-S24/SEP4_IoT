#include "temperature.h"
#include "dht11.h"
#include "stdio.h"
#include "stdlib.h"

#define NUM_READINGS 180 // Number of readings for 3 minutes (assuming 1 reading every second)
static uint8_t temperature_readings[NUM_READINGS];
static uint8_t current_reading_index = 0;

void temperature_init() {
    dht11_init();
}

uint8_t temperature_get_integer() {
    uint8_t temperature_integer;
    uint8_t temperature_decimal;

    if (dht11_get(NULL, NULL, &temperature_integer, &temperature_decimal) == DHT11_OK) {
        return temperature_integer;
    }

    return 0; // Return 0 if temperature reading fails
}

uint8_t temperature_get_decimal() {
    uint8_t temperature_integer;
    uint8_t temperature_decimal;

    if (dht11_get(NULL, NULL, &temperature_integer, &temperature_decimal) == DHT11_OK) {
        return temperature_decimal;
    }

    return 0; // Return 0 if temperature reading fails
}

float temperature_get_combined_value()
{
    uint8_t integer = temperature_get_integer;
    uint8_t decimal = temperature_get_decimal;


    float combine = integer + (decimal / 100.0);

    return combine;
}
