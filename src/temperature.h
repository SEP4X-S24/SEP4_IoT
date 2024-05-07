
#pragma once
#include <stdint.h>

void temperature_init();
uint8_t temperature_get_decimal();
uint8_t temperature_get_integer();
float temperature_get_combined_value();
