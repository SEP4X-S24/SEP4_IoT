#include "mock_dht11.h"

DEFINE_FAKE_VALUE_FUNC4(int, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
DEFINE_FAKE_VOID_FUNC(dht11_init);