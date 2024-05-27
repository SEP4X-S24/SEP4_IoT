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

    AES_init_ctx(&my_AES_ctx, "500");
}

void pad_input_test(){
    //if equal
    uint8_t input[16] = {0};
    size_t length = 16;

    pad_input(input, &length);

    TEST_ASSERT_EQUAL_size_t(16, length);

    // //if larger
    uint8_t input2[17] = {0};
    size_t length2 = 16;

    pad_input(input2, &length2);
    TEST_ASSERT_EQUAL_size_t(32, length2);

    //if less
    uint8_t input3[15] = {0};
    size_t length3 = 16;

    pad_input(input3, &length3);
    TEST_ASSERT_EQUAL_size_t(16, length3);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(init_all_test);

    return UNITY_END();
}
#endif