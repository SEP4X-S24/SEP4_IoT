#pragma once

#include <stdint.h>
#include "fff.h"
#define DHT11_OK 0
#define DHT11_ERROR -1

DECLARE_FAKE_VALUE_FUNC4(int, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
DECLARE_FAKE_VOID_FUNC(dht11_init);