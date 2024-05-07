#include "humidity.h"
#include "dht11.h"
#include "stdio.h"
#include "stdlib.h"

void humidity_init() {
    dht11_init();
}

uint8_t humidity_get_integer() {
    uint8_t humidity_integer;
    uint8_t humidity_decimal;

    if (dht11_get(&humidity_integer, &humidity_decimal, NULL, NULL) == DHT11_OK) {
        return humidity_decimal;
    }

    return 0; // Return 0 if humidity reading fails
}

uint8_t humidity_get_decimal() {
    uint8_t humidity_integer;
    uint8_t humidity_decimal;

    if (dht11_get(&humidity_integer, &humidity_decimal, NULL, NULL) == DHT11_OK) {
        return humidity_decimal;
    }

    return 0; // Return 0 if humidity reading fails
}

float humidity_get_combined_value()
{
    uint8_t integer = humidity_get_integer();
    uint8_t decimal = humidity_get_decimal();

    float combine = integer + (decimal / 100.0);

    return combine;
}

