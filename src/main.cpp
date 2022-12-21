#include <iostream>
#include "termDisplay/termDisplay.h"

int main(void)
{
    if (!td_initialize(40, 20))
    {
        return -1;
    }

    td_drawStrokeRect(2, 2, 5, 5, '#', TD_COLOR_WHITE, TD_COLOR_WHITE);
    // td_drawFillRect(3,3, 3, 3, '.', TD_COLOR_WHITE, TD_COLOR_DEFAULT);
    td_drawPoint(3, 3, '@', TD_COLOR_YELLOW, TD_COLOR_DEFAULT);
    td_drawRect(10, 7, 22, 12, 's', 'f', TD_COLOR_YELLOW, TD_COLOR_MAGENTA, TD_COLOR_WHITE, TD_COLOR_RED);
    td_display();

    td_terminate();

    while (getch() != 'e')
    {
        
    }

    return 0;
}
