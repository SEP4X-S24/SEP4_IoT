#pragma once
#include <unity.h>
#include "fff.h"
#include "temperature_humidity.h"
#include "dht11.h"
#include "weather.h"
#include "wifi.h"

DECLARE_FAKE_VOID_FUNC(dht11_init);
DECLARE_FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
DECLARE_FAKE_VOID_FUNC(cli);
DECLARE_FAKE_VOID_FUNC(sei);
DECLARE_FAKE_VOID_FUNC(light_init);
DECLARE_FAKE_VALUE_FUNC(uint16_t, light_read);
DECLARE_FAKE_VOID_FUNC(display_init);
DECLARE_FAKE_VOID_FUNC(display_int, int16_t);
//DECLARE_FAKE_VOID_FUNC(_delay_ms, double);
DECLARE_FAKE_VOID_FUNC(_delay_ms, int);
#ifdef WEATHER
DECLARE_FAKE_VALUE_FUNC(TempHumid, temperature_humidity_get_combined_values);
#endif
#ifdef MAIN
DECLARE_FAKE_VOID_FUNC(wifi_init);
DECLARE_FAKE_VOID_FUNC(weather_init);
DECLARE_FAKE_VOID_FUNC(display_setValues, uint8_t, uint8_t, uint8_t, uint8_t);
DECLARE_FAKE_VALUE_FUNC(TempHumidLight, updateWeather);
DECLARE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t*, uint16_t);
DECLARE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_join_AP, char*, char*);
DECLARE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_create_TCP_connection, char*, uint16_t, WIFI_TCP_Callback_t, char*);
DECLARE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_close_TCP_connection);
#else
//DECLARE_FAKE_VOID_FUNC(_delay_ms, double);
#endif