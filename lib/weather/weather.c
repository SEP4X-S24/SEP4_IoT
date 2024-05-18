#include "weather.h"
#include "temperature_humidity.h"
#include "light.h"
#include "display.h"
#include "dht11.h"
#ifdef WINDOWS_TEST
#else
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#define NUM_READINGS 3

void weather_init(){
    
    dht11_init();
    light_init();
    display_init();
}

TempHumidLight updateWeather(){
    uint16_t temperatureSum = 0;
    uint16_t humiditySum = 0;
    uint16_t lightSum = 0;
    TempHumid tempandhumid;
    TempHumidLight temphumidlight;
    double second = 1000;
    for (int i = 0; i < NUM_READINGS; i++) {
        cli();
        tempandhumid = temperature_humidity_get_combined_values();
        sei();
        temperatureSum += tempandhumid.temp;
        humiditySum += tempandhumid.humid;
        _delay_ms(50);
        cli();
        lightSum += light_read();
        sei();
        _delay_ms(50);
        display_int(i);
        _delay_ms(second);
    }

    uint16_t temperatureAvg = temperatureSum / NUM_READINGS;
    uint16_t lightAvg = lightSum / NUM_READINGS;
    uint16_t humidAvg = humiditySum / NUM_READINGS;

    temphumidlight.temp = temperatureAvg;
    temphumidlight.humid = humidAvg;
    temphumidlight.light = lightAvg;


    
    display_int((int)temperatureAvg);
    _delay_ms(second);
    display_int((int)humidAvg);
    _delay_ms(second);
    display_int((int)lightAvg);
    _delay_ms(second);

    return temphumidlight;
}
