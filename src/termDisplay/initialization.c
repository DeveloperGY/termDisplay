#include "termDisplay.h"

int TD_WIDTH  = 0;
int TD_HEIGHT = 0;
char **TD_CHAR_BUFFER    = NULL;
int **TD_FG_COLOR_BUFFER = NULL;
int **TD_BG_COLOR_BUFFER = NULL;
char *TD_PRINT_BUFFER    = NULL;

/**
 * @brief Initializes the character buffer if it hasn't already been initialized
 * 
 * @return 1 on success 0 on failure
*/
int initializeCharBuffer();

/**
 * @brief Initializes the foreground color buffer if it hasn't beed already
 * 
 * @return 1 on success 0 on failure
*/
int initializeFGColorBuffer();

/**
 * @brief Initializes the background color buffer if it hasn't been already
 * 
 * @return 1 on success 0 on failure
*/
int initializeBGColorBuffer();

/**
 * @brief Initializes the print buffer if it hasn't been already
 * 
 * @return 1 on success 0 on failure
*/
int initializePrintBuffer();

/**
 * @brief Uninitializes the character buffer if it hasn't been already
 * 
*/
void terminateCharBuffer();

/**
 * @brief Uninitializes the foreground color buffer if it hasnt been already
 * 
*/
void terminateFGColorBuffer();

/**
 * @brief Uninitializes the background color buffer if it hasn't been already
 * 
*/
void terminateBGColorBuffer();

/**
 * @brief Uninitializes the print buffer if it hasn't been already
 * 
*/
void terminatePrintBuffer();

int td_initialize(int width, int height)
{
    TD_WIDTH = width;
    TD_HEIGHT = height;

    if (!initializeCharBuffer())
    {
        TD_WIDTH = 0;
        TD_HEIGHT = 0;
        return 0;
    }

    if (!initializeFGColorBuffer())
    {
        terminateCharBuffer();
        TD_WIDTH = 0;
        TD_HEIGHT = 0;
        return 0;
    }

    if (!initializeBGColorBuffer())
    {
        terminateFGColorBuffer();
        terminateCharBuffer();
        TD_WIDTH = 0;
        TD_HEIGHT = 0;
        return 0;
    }

    if (!initializePrintBuffer())
    {
        terminateBGColorBuffer();
        terminateFGColorBuffer();
        terminateCharBuffer();
        TD_WIDTH = 0;
        TD_HEIGHT = 0;
        return 0;
    }

    printf("\x1b[?25l\x1b[H\x1b[2J");

    return 1;
}

void td_terminate(int clear)
{
    terminateCharBuffer();
    terminateFGColorBuffer();
    terminateBGColorBuffer();
    terminatePrintBuffer();
    
    TD_WIDTH = 0;
    TD_HEIGHT = 0;

    if (clear)
    {
        printf("\x1b[1;1H\x1b[2J");
    }

    printf("\x1b[?25h");
    return;
}

int initializeCharBuffer()
{
    if (!(TD_WIDTH != 0 && TD_HEIGHT != 0)) // API not initialized
    {
        return 0;
    }

    if (TD_CHAR_BUFFER) // already initialized, if you want to change the size, terminate the current api first and re initalize it
    {
        return 0;
    }

    TD_CHAR_BUFFER = (char **)malloc(sizeof(char *) * TD_HEIGHT);

    if (!TD_CHAR_BUFFER) // malloc failed
    {
        return 0;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        TD_CHAR_BUFFER[i] = malloc(sizeof(char) * TD_WIDTH);

        if (!TD_CHAR_BUFFER[i]) // malloc failed
        {
            for (int j=0; j<i; j++) // free previously allocated char memory
            {
                free(TD_CHAR_BUFFER[j]);
            }

            free(TD_CHAR_BUFFER);
            TD_CHAR_BUFFER = NULL;
            return 0;
        }
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            TD_CHAR_BUFFER[i][j] = ' ';
        }
    }

    return 1;
}

int initializeFGColorBuffer()
{
    if (!(TD_WIDTH && TD_HEIGHT)) // API not initialized
    {
        return 0;
    }

    if (TD_FG_COLOR_BUFFER) // already initialized, if you want to change the size, terminate the current api first and re initalize it
    {
        return 0;
    }

    TD_FG_COLOR_BUFFER = (int **)malloc(sizeof(int *) * TD_HEIGHT);

    if (!TD_FG_COLOR_BUFFER) // malloc failed
    {
        return 0;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        TD_FG_COLOR_BUFFER[i] = malloc(sizeof(int) * TD_WIDTH);

        if (!TD_FG_COLOR_BUFFER[i]) // malloc failed
        {
            for (int j=0; j<i; j++) // free previously allocated char memory
            {
                free(TD_FG_COLOR_BUFFER[j]);
            }

            free(TD_FG_COLOR_BUFFER);
            TD_FG_COLOR_BUFFER = NULL;
            return 0;
        }
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            TD_FG_COLOR_BUFFER[i][j] = TD_COLOR_DEFAULT;
        }
    }

    return 1;
}

int initializeBGColorBuffer()
{
    if (!(TD_WIDTH && TD_HEIGHT)) // API not initialized
    {
        return 0;
    }

    if (TD_BG_COLOR_BUFFER) // already initialized, if you want to change the size, terminate the current api first and re initalize it
    {
        return 0;
    }

    TD_BG_COLOR_BUFFER = (int **)malloc(sizeof(int *) * TD_HEIGHT);

    if (!TD_BG_COLOR_BUFFER) // malloc failed
    {
        return 0;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        TD_BG_COLOR_BUFFER[i] = malloc(sizeof(int) * TD_WIDTH);

        if (!TD_BG_COLOR_BUFFER[i]) // malloc failed
        {
            for (int j=0; j<i; j++) // free previously allocated char memory
            {
                free(TD_BG_COLOR_BUFFER[j]);
            }

            free(TD_BG_COLOR_BUFFER);
            TD_BG_COLOR_BUFFER = NULL;
            return 0;
        }
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            TD_BG_COLOR_BUFFER[i][j] = TD_COLOR_DEFAULT + TD_FG_TO_BG_OFFSET;
        }
    }

    return 1;
}

int initializePrintBuffer()
{
    if (!(TD_WIDTH && TD_HEIGHT)) // API not initialized
    {
        return 0;
    }

    if (TD_PRINT_BUFFER) // already initialized, if you want to change the size, terminate the current api first and re initalize it
    {
        return 0;
    }

    size_t size = (12 * TD_WIDTH * TD_HEIGHT) + TD_HEIGHT + 1;

    TD_PRINT_BUFFER = (char *)malloc(size);

    if (!TD_PRINT_BUFFER) // malloc failed
    {
        return 0;
    }

    return 1;
}

void terminateCharBuffer()
{
    if (!TD_CHAR_BUFFER) // Already deallocated
    {
        return;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        free(TD_CHAR_BUFFER[i]);
    }

    free(TD_CHAR_BUFFER);
    TD_CHAR_BUFFER = NULL;
}

void terminateFGColorBuffer()
{
    if (!TD_FG_COLOR_BUFFER) // Already deallocated
    {
        return;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        free(TD_FG_COLOR_BUFFER[i]);
    }

    free(TD_FG_COLOR_BUFFER);
    TD_FG_COLOR_BUFFER = NULL;
}

void terminateBGColorBuffer()
{
    if (!TD_BG_COLOR_BUFFER) // Already deallocated
    {
        return;
    }

    for (int i=0; i<TD_HEIGHT; i++)
    {
        free(TD_BG_COLOR_BUFFER[i]);
    }

    free(TD_BG_COLOR_BUFFER);
    TD_BG_COLOR_BUFFER = NULL;
}

void terminatePrintBuffer()
{
    if (!TD_PRINT_BUFFER) // Already deallocated
    {
        return;
    }

    free(TD_PRINT_BUFFER);
    TD_PRINT_BUFFER = NULL;
}