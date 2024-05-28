#include "application.h"

int main()
{
    init_all();
    sei();

    display_setValues(9, 9, 9, 9);
    while (1)
    {
        app_start();
    }
}
