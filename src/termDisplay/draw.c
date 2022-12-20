#include "termDisplay.h"

void td_display()
{
    if (!TD_BUFFER)
    {
        return;
    }

	printf("\e[1;1H\e[2J"); // Clear the terminal using escape sequences

    for (int i=0; i<TD_HEIGHT; i++)
    {
        printf("%s\n", TD_BUFFER[i]);
    }
    return;
}

void td_drawPoint(int x, int y, char c)
{
    if (!TD_BUFFER)
    {
        return;
    }

    if (x < 0 || x >= TD_WIDTH || y < 0 || y >= TD_HEIGHT)
    {
        return;
    }

    TD_BUFFER[y][x] = c;    
    
    return;
}
