#include "fff.h"
#include "mocks.h"

DEFINE_FAKE_VOID_FUNC(dht11_init);
DEFINE_FAKE_VALUE_FUNC(uint8_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
DEFINE_FAKE_VOID_FUNC(cli);
DEFINE_FAKE_VOID_FUNC(sei);
DEFINE_FAKE_VOID_FUNC(_delay_ms, double);
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
#endif