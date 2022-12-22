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
        td_drawTextHorizontal(0, 0, "Name: korpine", TD_COLOR_YELLOW, TD_COLOR_DEFAULT);
        td_drawPoint(x, y, '@', TD_COLOR_CYAN, TD_COLOR_DEFAULT);
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
