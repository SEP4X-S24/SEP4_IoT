#ifdef TEMP_HUMID
#include <unity.h>
#include "temperature_humidity.h"
#include "fff.h"
#include "mocks.h"

DEFINE_FFF_GLOBALS

#define DHT11_OK 0
#define DHT11_ERROR -1

void setUp(void){
    RESET_FAKE(dht11_init);
    RESET_FAKE(dht11_get);
    RESET_FAKE(display_init);
    RESET_FAKE(light_init);
}
void tearDown(void) {}

uint8_t custom_dht11_get(uint8_t* hI, uint8_t* hD, uint8_t* tI, uint8_t* tD) {
    *hI = 60;  // Humidity integer
    *hD = 0;   // Humidity decimal
    *tI = 25;  // Temperature integer
    *tD = 0;   // Temperature decimal
    return DHT11_OK;
}

void test_temperature_humidity_get_combined_values_success() {
    dht11_get_fake.return_val = DHT11_OK;
    dht11_get_fake.custom_fake = custom_dht11_get;

    TempHumid result = temperature_humidity_get_combined_values();

    TEST_ASSERT_EQUAL_UINT8(25, result.temp);
    TEST_ASSERT_EQUAL_UINT8(60, result.humid);
}

void test_temperature_humidity_get_combined_values_failure() {
    dht11_get_fake.return_val = DHT11_ERROR;

    TempHumid result = temperature_humidity_get_combined_values();

    TEST_ASSERT_EQUAL_INT(1, display_int_fake.call_count);
    TEST_ASSERT_EQUAL_INT(7777, display_int_fake.arg0_val);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_temperature_humidity_get_combined_values_success);
    RUN_TEST(test_temperature_humidity_get_combined_values_failure);

    return UNITY_END();
}
#endif
