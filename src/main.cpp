#include <iostream>
#include "termDisplay/termDisplay.h"

int main(void)
{
    if (!td_initialize(40, 20))
    {
        return -1;
    }

    char ch;

    int x = 3;
    int y = 3;

    while (ch != 'q')
    {
        td_drawStrokeRect(2, 2, 5, 5, '#', TD_COLOR_WHITE, TD_COLOR_WHITE);
        td_drawFillRect(3,3, 3, 3, '.', TD_COLOR_WHITE, TD_COLOR_DEFAULT);
        td_drawRect(10, 7, 22, 12, 's', 'f', TD_COLOR_YELLOW, TD_COLOR_MAGENTA, TD_COLOR_WHITE, TD_COLOR_RED);
        td_drawLine(0, 0, 10, 4, '*', TD_COLOR_RED, TD_COLOR_CYAN);
        td_drawLine(0, 4, 10, 0, '*', TD_COLOR_BLACK, TD_COLOR_BLUE);
        td_drawLine(0, 0, 4, 10, '*', TD_COLOR_CYAN, TD_COLOR_RED);
        td_drawLine(0, 10, 4, 0, '*', TD_COLOR_BLUE, TD_COLOR_BLACK);
        td_drawPoint(x, y, '@', TD_COLOR_YELLOW, TD_COLOR_DEFAULT);
        td_display();

        ch = getch();

        if (ch == 'd')
        {
            x++;
        }
        if (ch == 'a')
        {
            x--;
        }
        if (ch == 'w')
        {
            y--;
        }
        if (ch == 's')
        {
            y++;
        }
    }

    td_terminate();

    return 0;
}
