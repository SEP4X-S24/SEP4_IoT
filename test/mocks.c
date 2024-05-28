#include "fff.h"
#include "mocks.h"

DEFINE_FAKE_VOID_FUNC(dht11_init);
DEFINE_FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
DEFINE_FAKE_VOID_FUNC(cli);
DEFINE_FAKE_VOID_FUNC(sei);
DEFINE_FAKE_VOID_FUNC(light_init);
DEFINE_FAKE_VALUE_FUNC(uint16_t, light_read);
DEFINE_FAKE_VOID_FUNC(display_init);
DEFINE_FAKE_VOID_FUNC(display_int, int16_t);
#ifdef WEATHER
DEFINE_FAKE_VALUE_FUNC(TempHumid, temperature_humidity_get_combined_values);
#endif
#ifdef MAIN
DEFINE_FAKE_VOID_FUNC(wifi_init);
DEFINE_FAKE_VOID_FUNC(weather_init);
DEFINE_FAKE_VOID_FUNC(_delay_ms, int);
DEFINE_FAKE_VOID_FUNC(display_setValues, uint8_t, uint8_t, uint8_t, uint8_t);
DEFINE_FAKE_VALUE_FUNC(TempHumidLight, updateWeather);
DEFINE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t*, uint16_t);
DEFINE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_join_AP, char*, char*);
DEFINE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_create_TCP_connection,  char*, uint16_t, WIFI_TCP_Callback_t, char*);
DEFINE_FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_close_TCP_connection);
#else
DEFINE_FAKE_VOID_FUNC(_delay_ms, double);
#endif