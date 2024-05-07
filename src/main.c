#include <util/delay.h>
#include <stdlib.h>
#include "display.h"
#include "dht11.h"
#include "wifi.h"
#include "weather.h"

int main()
{
    // wifi_init();
    // wifi_command_join_AP("cubeco", "arina123");
    // wifi_command_create_TCP_connection("172.20.10.3", 24, NULL, NULL);
    weather_init();
    display_init();
    float tempHumidLight[] = {0,0,0};

    while (1)
    {
        updateWeather(tempHumidLight);
        //send tempHumidLight to backend
        //weather.updateWeather(tempHumidLight) updates the three three minute averages
        //this should probably not be in a while(true) loop, but that will be when we figure out connection
    }
}