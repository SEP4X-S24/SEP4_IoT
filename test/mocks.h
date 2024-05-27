#pragma once
#include <unity.h>
#include "fff.h"
#include "temperature_humidity.h"
#include "dht11.h"

DECLARE_FAKE_VOID_FUNC(dht11_init);
DECLARE_FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
DECLARE_FAKE_VOID_FUNC(cli);
DECLARE_FAKE_VOID_FUNC(sei);
DECLARE_FAKE_VOID_FUNC(light_init);
DECLARE_FAKE_VALUE_FUNC(uint16_t, light_read);
DECLARE_FAKE_VOID_FUNC(display_init);
DECLARE_FAKE_VOID_FUNC(display_int, int16_t);
#ifdef WEATHER
DECLARE_FAKE_VALUE_FUNC(TempHumid, temperature_humidity_get_combined_values);
DECLARE_FAKE_VOID_FUNC(_delay_ms, double);
#endif
#ifdef MAIN
DECLARE_FAKE_VOID_FUNC(wifi_init);
DECLARE_FAKE_VOID_FUNC(weather_init);
DECLARE_FAKE_VOID_FUNC(_delay_ms, int);
#else
DEFINE_FAKE_VOID_FUNC(_delay_ms, double);
#endif