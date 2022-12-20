#include <iostream>
#include "termDisplay/termDisplay.h"

int main(void)
{
    if (!td_initialize(20, 10))
    {
        return -1;
    }
    
    td_drawPoint(3, 3, '@');
    td_display();

    td_terminate();
    return 0;
}
