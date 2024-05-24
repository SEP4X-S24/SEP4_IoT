#ifdef WEATHER

#include <unity.h>
#include "weather.h"
#include "temperature_humidity.h"
#include "fff.h"
#include "mocks.h"

DEFINE_FFF_GLOBALS

// SETUP
void setUp(void){
    RESET_FAKE(dht11_init);
    RESET_FAKE(dht11_get);
    RESET_FAKE(display_init);
    RESET_FAKE(light_init);
}
void tearDown(void) {}

// CUSTOM FAKE FUNCTIONS
TempHumid custom_temperature_humidity_get_combined_values() {
    TempHumid dummyData;
    dummyData.temp = 25;
    dummyData.humid = 60;

    return dummyData;
}

uint16_t custom_light_read(){
    uint16_t light = 93;
    return light;
}

// TESTS
void weather_init_test(){
    weather_init();

    TEST_ASSERT_EQUAL(1, dht11_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, light_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, display_init_fake.call_count);
}

void updateWeather_test(){
    temperature_humidity_get_combined_values_fake.custom_fake = custom_temperature_humidity_get_combined_values;
    light_read_fake.custom_fake = custom_light_read;
    TempHumidLight result = updateWeather();

    TEST_ASSERT_EQUAL_UINT16(25, result.temp);
    TEST_ASSERT_EQUAL_UINT16(93, result.light);    
    TEST_ASSERT_EQUAL_UINT16(60, result.humid);    
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(weather_init_test);
    RUN_TEST(updateWeather_test);

    return UNITY_END();
}
#endif