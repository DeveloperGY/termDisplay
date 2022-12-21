#include "termDisplay.h"

char getch() 
{
    char ch;

    struct termios old;
    struct termios new;

    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new);
    ch = (char)getchar();
    tcsetattr(0, TCSANOW, &old);

    return ch;
}