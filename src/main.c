#include "wifi.h"
#include "display.h"
#include "buttons.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    wifi_init();
    wifi_command_join_AP("Pixel de Hugo", "Lumia535");
    wifi_command_create_TCP_connection("192.168.205.61", 23, NULL, NULL);
    display_init();
    buttons_init();
    //display_setValues(9,4,1,5);
    // display_int(14);
    // display_letters('h','h','h','h');
    uint8_t value = 0;
    bool prev_state_1 = false;
    bool prev_state_3 = false;
    while (1)
    {
        bool current_state_1 = buttons_1_pressed();
        // wifi_command_TCP_transmit("Hi there\n", 9);
        // _delay_ms(2000);
        if(current_state_1 && !prev_state_1){
            value++;
            display_int(value);
            // _delay_ms(100);
        }
        prev_state_1 = current_state_1;

        bool current_state_3 = buttons_3_pressed();
        if(current_state_3 && !prev_state_3){
            value--;
            display_int(value);
            _delay_ms(50);
        }

        prev_state_3 = current_state_3;
    }  
}