#include "temperature_humidity.h"

TempHumid temperature_humidity_get_combined_values() {
    TempHumid dummyData;
    dummyData.temp = 25;
    dummyData.humid = 60;

    return dummyData;
}