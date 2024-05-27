#ifdef MAIN

#include <unity.h>
#include "fff.h"
#include "mocks.h"
#include "main_functionality.h"

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

int main(void){
    UNITY_BEGIN();
    RUN_TEST(init_all_test);

    return UNITY_END();
}
#endif