#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <stdint.h>

// Function prototypes
void humidity_init();
uint8_t humidity_get_decimal();
uint8_t humidity_get_integer();
float humidity_get_combined_value();

#endif // HUMIDITY_H
