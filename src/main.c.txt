#include "includes.h"
#include "periodic_task.h"
#include "pc_comm.h"
#include "display.h"
#include "leds.h"
#include "servo.h"
#include "tone.h"
#include "light.h"
#include "pir.h"


void func_a(){
//static uint16_t i = -10;
//display_int(i++);

pc_comm_send_string_blocking("!!!!!!!!!!!!!!!!!!!!!");
}

void func_b(){
    static uint8_t state = 0;
    if (state==0)
    {
        servo(50);
        state = 1;
    }
    else {
        servo(100);
        state = 0;
    }
    

}

void func_c(){

sei();
pc_comm_send_string_blocking("   _______________                        |*\\_/*|________\n"
"  |  ___________  |     .-.     .-.      ||_/-\\_|______  |\n"
"  | |           | |    .****. .****.     | |           | |\n"
"  | |   0   0   | |    .*****.*****.     | |   0   0   | |\n"
"  | |     -     | |     .*********.      | |     -     | |\n"
"  | |   \\___/   | |      .*******.       | |   \\___/   | |\n"
"  | |___     ___| |       .*****.        | |___________| |\n"
"  |_____|\\_/|_____|        .***.         |_______________|\n"
"    _|__|/ \\|_|_.............*.............._|________|_\n"
"   / ********** \\                          / ********** \\\n"
" /  ************  \\                      /  ************  \\\n"
"--------------------                    --------------------\n");

}
int16_t globalcounter=0;
void func2(){
    globalcounter++;
    

}
int main(void)
{

    display_init();     
    //light_init();
    pir_init(func2);

 

while (1)
{
    display_int(globalcounter);
    _delay_ms(500);
   
}

   


    return 0;
}
