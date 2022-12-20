#include "termDisplay.h"

int TD_WIDTH     = 0;
int TD_HEIGHT    = 0;
char **TD_BUFFER = NULL;

int td_initialize(int width, int height)
{
    TD_WIDTH = width;
    TD_HEIGHT = height;

    TD_BUFFER = (char **)malloc(sizeof(char *) * TD_HEIGHT);

    if (!TD_BUFFER) // Failed to allocate memory for buffer rows
    {
        TD_WIDTH = 0;
        TD_HEIGHT = 0;
        TD_BUFFER = NULL;
        return 0;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        TD_BUFFER[i] = (char *)malloc(sizeof(char) * (TD_WIDTH+1));

        if (!TD_BUFFER[i]) // Failed to allocate memory for Frame String
        {
            for (int j=0; j<i; j++) // Deallocate Allocated Frame Strings
            {
                free(TD_BUFFER[j]);
            }

            free(TD_BUFFER);

            TD_WIDTH = 0;
            TD_HEIGHT = 0;
            TD_BUFFER= NULL;

            return 0;
        }

        TD_BUFFER[i][TD_WIDTH] = '\0';
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            TD_BUFFER[i][j] = ' ';
        }
    }

    return 1;
}

void td_terminate()
{
    for (int i=0; i<TD_HEIGHT; i++)
    {
        free(TD_BUFFER[i]); // Deallocate Frame Strings
    }

    free(TD_BUFFER); // Deallocate Frame
    
    TD_WIDTH = 0;
    TD_HEIGHT = 0;
    TD_BUFFER = NULL;
    return;
}
