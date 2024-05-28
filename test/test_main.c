#ifdef MAIN

#include <unity.h>
#include "fff.h"
#include "mocks.h"
#include "application.h"

DEFINE_FFF_GLOBALS

// SETUP
void setUp(void){}
void tearDown(void) {}

// CUSTOM FAKE FUNCTIONS

// TESTS
void init_all_test(){
    init_all();

    TEST_ASSERT_EQUAL(1, wifi_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, weather_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, display_init_fake.call_count);
}

void pad_input_test(){
    //if equal
    uint8_t input[16] = {0};
    size_t length = 16;

    pad_input(input, &length);

    TEST_ASSERT_EQUAL_size_t(16, length);

    // //if larger
    char *jsonString = "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
    size_t length2 = 16;

    pad_input(jsonString, &length2);
    TEST_ASSERT_EQUAL_size_t(16, length2);

    //if less
    uint8_t input3[15] = {0};
    size_t length3 = 16;

    pad_input(input3, &length3);
    // TEST_ASSERT_EQUAL_size_t(32, length3);
}

TempHumidLight sampleValues = { 27.0, 60.0, 190.0 };
void create_and_send_weather_test(){
    updateWeather_fake.return_val = sampleValues;
    create_and_send_weather();
    TEST_ASSERT_EQUAL(1, updateWeather_fake.call_count);
    TEST_ASSERT_FALSE(ping_timeout);
    TEST_ASSERT_EQUAL(0, timeout_count);
}

// FAKE_VOID_FUNC(create_and_send_weather);
void update_data_test(){
    strcpy(received_message, "updateWeather");
    update_data();
    //2 cause it's been called from another method as well
    TEST_ASSERT_EQUAL(2, updateWeather_fake.call_count);
}

void wifi_connect_test(){
    wifi_command_create_TCP_connection_fake.return_val = WIFI_OK;
    WIFI_ERROR_MESSAGE_t result = wifi_connect();
    TEST_ASSERT_EQUAL(WIFI_OK, result);
    TEST_ASSERT_EQUAL_STRING("Pixel de Hugo", wifi_command_join_AP_fake.arg0_val);
    TEST_ASSERT_EQUAL_STRING("Lumia535", wifi_command_join_AP_fake.arg1_val);
    TEST_ASSERT_EQUAL_STRING("20.13.143.114", wifi_command_create_TCP_connection_fake.arg0_val);
    TEST_ASSERT_EQUAL_INT(2228, wifi_command_create_TCP_connection_fake.arg1_val);
}

void app_start_test(){
    app_start();
    TEST_ASSERT_EQUAL_INT(6666, display_int_fake.arg0_val);
    TEST_ASSERT_EQUAL(1, wifi_command_close_TCP_connection_fake.call_count);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(init_all_test);
    // RUN_TEST(pad_input_test);
    RUN_TEST(create_and_send_weather_test);
    RUN_TEST(update_data_test);
    RUN_TEST(wifi_connect_test);
    RUN_TEST(app_start_test);
    return UNITY_END();
}
#endif