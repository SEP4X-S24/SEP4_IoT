#include "setup.h"

void setUp(void) {
    RESET_FAKE(dht11_get);
    RESET_FAKE(dht11_init);
    RESET_FAKE(display_int);
    FFF_RESET_HISTORY();
}

void tearDown(void) {
}