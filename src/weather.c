#include "weather.h"
#include "temperature.h"
#include "humidity.h"
#include "light.h"
#include "display.h"
#include "util/delay.h"

#define NUM_READINGS 180.0 

void weather_init(){
    temperature_init();
    light_init();
    humidity_init();
    display_init();
}

void updateWeather(float TempHumidLight[]){
    float temperatureSum = 0;
    float humiditySum = 0;
    float lightSum = 0;
    double second = 1000;
    for (int i = 0; i < NUM_READINGS; i++) {
        temperatureSum += temperature_get_combined_value();
        humiditySum += humidity_get_combined_value();
        lightSum += light_read();
        display_int(i);
        _delay_ms(second);
    }

    float temperatureAvg = temperatureSum / NUM_READINGS;
    float lightAvg = lightSum / NUM_READINGS;
    float humidAvg = humiditySum / NUM_READINGS;

    TempHumidLight[0] = temperatureAvg;
    TempHumidLight[1] = humidAvg;
    TempHumidLight[2] = lightAvg;


    
    display_int((int)temperatureAvg);
    _delay_ms(second);
    display_int((int)humidAvg);
    _delay_ms(second);
    display_int((int)lightAvg);
    _delay_ms(second);
}
