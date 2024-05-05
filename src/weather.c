#include "weather.h"
#include "temperature.h"
#define NUM_READINGS 180 // Number of readings for 3 minutes (assuming 1 reading every second)

void weather_init()
{
    temperature_init();
    light_init();
    humidity_init();
}

void updateWeather(float TempHumidLight[])
{
    float temperatureSum = 0;
    float humiditySum = 0;
    float lightSum = 0;

    for (int i = 0; i < NUM_READINGS; i++) {
        temperatureSum += temperature_get_combined_value();
        humiditySum += humidity_get_float();
        lightSum += light_get_float();

        _delay_ms(1000)
    }

    float temperatureAvg = temperatureSum / NUM_READINGS;
    float lightAvg = lightSum / NUM_READINGS;
    float humidAvg = humiditySum / NUM_READINGS;

    TempHumidLight[0] = temperatureAvg;
    TempHumidLight[1] = humidAvg;
    TempHumidLight[2] = lightAvg;
}