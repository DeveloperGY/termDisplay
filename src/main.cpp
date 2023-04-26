#include <iostream>
#include "termDisplay/termDisplay.h"

int main(void)
{
    if (!td_initialize(84, 40))
    {
        return -1;
    }

    while (getch(0) != 'q')
    {
        td_drawPoint(0, 0, '*', TD_COLOR_WHITE, TD_COLOR_DEFAULT);
        td_drawPoint(40, 27, '*', TD_COLOR_WHITE, TD_COLOR_DEFAULT);
        td_drawLine(0, 27, 40, 0, '*', TD_COLOR_GREEN, TD_COLOR_DEFAULT);
        td_display();
    }

    td_terminate(0);

    return 0;
}
