#include "termDisplay.h"

char basic_getch()
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

// returns NULL if there was no character
// max wait time is in milliseconds
char getch(unsigned int max_wait_time) 
{
    char ch = NULL;

    fd_set rfds;
    struct timeval tv;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    tv.tv_sec = 0;
    tv.tv_usec = max_wait_time *10;

    int has_input = select(1, &rfds, NULL, NULL, &tv);

    if (has_input == 1)
    {
        ch = basic_getch();
    }

    return ch;
}