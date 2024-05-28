#include <unity.h>
#include "weather.h"
#include "temperature_humidity.h"
#include "fff.h"
#include "mocks.h"
#include "setup.h"

DEFINE_FFF_GLOBALS

// test_weather.
void weather_init_test(void);
// void updateWeather_test(void);

// test_temperature_humidity.c
void test_temperature_humidity_get_combined_values_success(void);
void test_temperature_humidity_get_combined_values_failure(void);

int main(void){
    UNITY_BEGIN();
    // test_weather.c
    RUN_TEST(weather_init_test);
    // RUN_TEST(updateWeather_test);

    // test_temperature_humidity.c
    RUN_TEST(test_temperature_humidity_get_combined_values_success);
    RUN_TEST(test_temperature_humidity_get_combined_values_failure);

    return UNITY_END();
}
