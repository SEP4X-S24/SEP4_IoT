#pragma once
#include <stdint.h>

void humidity_init();
uint8_t humidity_get_decimal();
uint8_t humidity_get_integer();
float humidity_get_combined_value();