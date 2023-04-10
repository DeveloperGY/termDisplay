#include "termDisplay.h"

int TD_COLOR_DEFAULT = 39;
int TD_COLOR_BLACK   = 30;
int TD_COLOR_RED     = 31;
int TD_COLOR_GREEN   = 32;
int TD_COLOR_YELLOW  = 33;
int TD_COLOR_BLUE    = 34;
int TD_COLOR_MAGENTA = 35;
int TD_COLOR_CYAN    = 36;
int TD_COLOR_WHITE   = 37;

int TD_FG_TO_BG_OFFSET = 10;

void td_display()
{
    if (!(TD_CHAR_BUFFER && TD_FG_COLOR_BUFFER && TD_BG_COLOR_BUFFER))
    {
        return;
    }

    // reset the cursor to the top left with ansi escape sequences
    printf("\x1b[H");

    char fg_color_str[3];
    char bg_color_str[3];

    size_t index = 0;

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            snprintf(fg_color_str, 3, "%d", TD_FG_COLOR_BUFFER[i][j]);
            snprintf(bg_color_str, 3, "%d", TD_BG_COLOR_BUFFER[i][j]);

            TD_PRINT_BUFFER[index++] = '\x1b';
            TD_PRINT_BUFFER[index++] = '[';
            TD_PRINT_BUFFER[index++] = fg_color_str[0];
            TD_PRINT_BUFFER[index++] = fg_color_str[1];
            TD_PRINT_BUFFER[index++] = ';';
            TD_PRINT_BUFFER[index++] = bg_color_str[0];
            TD_PRINT_BUFFER[index++] = bg_color_str[1];
            TD_PRINT_BUFFER[index++] = 'm';
            TD_PRINT_BUFFER[index++] = TD_CHAR_BUFFER[i][j];
            TD_PRINT_BUFFER[index++] = '\x1b';
            TD_PRINT_BUFFER[index++] = '[';
            TD_PRINT_BUFFER[index++] = 'm';
        }
        TD_PRINT_BUFFER[index++] = '\n';
    }

    TD_PRINT_BUFFER[index] = '\0';

    printf("%s", TD_PRINT_BUFFER);

    for (int i=0; i<TD_HEIGHT; i++)
    {
        for (int j=0; j<TD_WIDTH; j++)
        {
            TD_CHAR_BUFFER[i][j] = ' ';
            TD_FG_COLOR_BUFFER[i][j] = TD_COLOR_DEFAULT;
            TD_BG_COLOR_BUFFER[i][j] = TD_COLOR_DEFAULT + TD_FG_TO_BG_OFFSET;
        }
    }

    return;
}

void td_drawPoint(int x, int y, char c, int fgColor, int bgColor)
{
    if (!(TD_CHAR_BUFFER && TD_FG_COLOR_BUFFER && TD_BG_COLOR_BUFFER))
    {
        return;
    }

    if (x < 0 || x >= TD_WIDTH || y < 0 || y >= TD_HEIGHT)
    {
        return;
    }

    TD_CHAR_BUFFER[y][x] = c;
    TD_FG_COLOR_BUFFER[y][x] = fgColor;
    TD_BG_COLOR_BUFFER[y][x] = bgColor + TD_FG_TO_BG_OFFSET;
    
    return;
}

void td_drawStrokeRect(int x, int y, unsigned int width, unsigned int height, char c, int fgColor, int bgColor)
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (i == 0 || i == height-1 || j == 0 || j == width - 1)
            {
                td_drawPoint(j+x, i+y, c, fgColor, bgColor);
            }
        }
    }
    return;
}

void td_drawFillRect(int x, int y, unsigned int width, unsigned int height, char c, int fgColor, int bgColor)
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            td_drawPoint(j+x, i+y, c, fgColor, bgColor);
        }
    }
    return;
}

void td_drawRect(int x, int y, unsigned int width, unsigned int height, char stroke, char fill, int strokeFGColor, int strokeBGColor, int fillFGColor, int fillBGColor)
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (i == 0 || i == height-1 || j == 0 || j == width - 1)
            {
                td_drawPoint(j+x, i+y, stroke, strokeFGColor, strokeBGColor);
            }
            else
            {
                td_drawPoint(j+x, i+y, fill, fillFGColor, fillBGColor);
            }
        }
    }
    return;
}

void td_drawLine(int x1, int y1, int x2, int y2, char c, int fgColor, int bgColor)
{
    float slope = (double)(y2 - y1) / (double)(x2 - x1);

    int positiveSlope = slope >= 0;
    int majorSlope = fabs(slope) > 1;

    if (positiveSlope && !majorSlope)
    {
        if (x2 < x1) // swap to make the line always go left to right
        {
            int temp = x2;
            x2 = x1;
            x1 = temp;

            temp = y2;
            y2 = y1;
            y1 = temp;
        }

        int yOffset = 0;

        for (int i=0; i<=x2-x1; i++)
        {
            double y = slope * (i + x1);
            if (y - 0.5 >= yOffset)
            {
                yOffset++;
            }
            td_drawPoint(x1 + i, yOffset + y1, c, fgColor, bgColor);
        }
    }
    else if (!positiveSlope && !majorSlope)
    {
        if (x2 < x1) // swap to make the line always go left to right
        {
            int temp = x2;
            x2 = x1;
            x1 = temp;

            temp = y2;
            y2 = y1;
            y1 = temp;
        }
        int yOffset = 0;

        for (int i=0; i<=x2-x1; i++)
        {
            double y = slope * (i + x1);
            if (y + 0.5 <= yOffset)
            {
                yOffset--;
            }
            td_drawPoint(x1 + i, yOffset + y1, c, fgColor, bgColor);
        }
    }
    else if (positiveSlope && majorSlope)
    {
        if (y2 < y1) // swap to make the line always go left to right
        {
            int temp = x2;
            x2 = x1;
            x1 = temp;

            temp = y2;
            y2 = y1;
            y1 = temp;
        }

        int xOffset = 0;

        for (int i=0; i<=y2-y1; i++)
        {
            double x = (double)(i+y1)/slope;

            if (x - 0.5 >= xOffset)
            {
                xOffset++;
            }
            td_drawPoint(xOffset + x1, i + y1, c, fgColor, bgColor);
        }
    }
    else if (!positiveSlope && majorSlope)
    {
        if (y2 < y1) // swap to make the line always go left to right
        {
            int temp = x2;
            x2 = x1;
            x1 = temp;

            temp = y2;
            y2 = y1;
            y1 = temp;
        }

        int xOffset = 0;

        for (int i=0; i<=y2-y1; i++)
        {
            double x = (double)(i+y1)/slope;

            if (x + 0.5 <= xOffset)
            {
                xOffset--;
            }
            td_drawPoint(xOffset + x1, i + y1, c, fgColor, bgColor);
        }
    }

    return;
}

void td_drawTextHorizontal(int x, int y, const char *str, int fgColor, int bgColor)
{
    size_t len = strlen(str);

    for (int i=0; i<len; i++)
    {
        td_drawPoint(x+i, y, str[i], fgColor, bgColor);
    }

    return;
}

void td_drawTextVertical(int x, int y, const char *str, int fgColor, int bgColor)
{
    size_t len = strlen(str);

    for (int i=0; i<len; i++)
    {
        td_drawPoint(x, y+i, str[i], fgColor, bgColor);
    }

    return;
}