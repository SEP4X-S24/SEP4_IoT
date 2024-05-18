#include <unity.h>
#include "weather.h"
#include "fff.h"

DEFINE_FFF_GLOBALS

FAKE_VOID_FUNC(dht11_init);
FAKE_VALUE_FUNC(uint8_t, dht11_get, uint8_t, uint8_t, uint8_t, uint8_t);
FAKE_VOID_FUNC(cli);
FAKE_VOID_FUNC(sei);
FAKE_VOID_FUNC(_delay_ms, double);
FAKE_VOID_FUNC(light_init);
FAKE_VOID_FUNC(light_read);
FAKE_VOID_FUNC(display_init);
FAKE_VOID_FUNC(display_int, int16_t);

void setUp(void){
    RESET_FAKE(dht11_init);
    RESET_FAKE(dht11_get);
    RESET_FAKE(display_init);
    RESET_FAKE(light_init);
}
void tearDown(void) {}

void weather_test(){
    weather_init();

    TEST_ASSERT_EQUAL(1, dht11_init_fake.call_count);
    // TEST_ASSERT_EQUAL(1, light_init_fake.call_count);
    // TEST_ASSERT_EQUAL(1, display_init_fake.call_count);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(weather_test);

    return UNITY_END();
}