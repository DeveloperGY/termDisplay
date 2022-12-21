#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * @brief Width of the buffers
*/
extern int TD_WIDTH;

/**
 * @brief Height of the buffers
*/
extern int TD_HEIGHT;

/**
 * @brief Character display buffer
 * 
*/
extern char **TD_CHAR_BUFFER;

/**
 * @brief Foreground color buffer
 * 
*/
extern int **TD_FG_COLOR_BUFFER;

/**
 * @brief Background color buffer
 * 
*/
extern int **TD_BG_COLOR_BUFFER;

/**
 *  Colors
 *  Uses ansi escape sequences to display colors
 * 
 */
extern int TD_COLOR_DEFAULT;
extern int TD_COLOR_BLACK;
extern int TD_COLOR_RED;
extern int TD_COLOR_GREEN;
extern int TD_COLOR_YELLOW;
extern int TD_COLOR_BLUE;
extern int TD_COLOR_MAGENTA;
extern int TD_COLOR_CYAN;
extern int TD_COLOR_WHITE;

/**
 * @brief The offset between ansi color codes
*/
extern int TD_FG_TO_BG_OFFSET;

/**
 * Initialization Functions
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the library and allocates memory
 *
 * @param width width of the buffer
 * @param height height of the buffer
 *
 * @return Returns 1 on success and 0 on failure
 *
 */
int td_initialize(int width, int height);

/**
 * @brief Terminates the library and deallocates memory
 *
 */
void td_terminate();

#ifdef __cplusplus
}
#endif


/**
 * Draw Functions
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Draws the Frame Buffer to stdout
 *
 */
void td_display();
    
/**
 * @brief Draws a character at the specified coordinates
 *
 * @param x The X Coordinate
 * @param y The Y Coordinate
 * @param c The character to draw
 *
 * @param fgColor The foreground color of the character
 * @param bgColor The background color of the character
 * 
 */
void td_drawPoint(int x, int y, char c, int fgColor, int bgColor);

/**
 * @brief Draws the outline of a rectangle at the specified cordinates with the specified dimensions and colors
 * 
 * @param x The X Coordinate
 * @param y The Y Coordinate
 * @param c The character to draw
 * 
 * @param width The width
 * @param height The height
 * 
 * @param fgColor The foreground color of the character
 * @param bgColor The background color of the character
 *
*/
void td_drawStrokeRect(int x, int y, unsigned int width, unsigned int height, char c, int fgColor, int bgColor);

/**
 * @brief Draws a filled rectangle at the specified cordinates with the specified dimensions and colors
 * 
 * @param x The X Coordinate
 * @param y The Y Coordinate
 * @param c The character to draw
 *  * 
 * @param width The width
 * @param height The height
 * 
 * @param fgColor The foreground color of the character
 * @param bgColor The background color of the character
 *
*/
void td_drawFillRect(int x, int y, unsigned int width, unsigned int height, char c, int fgColor, int bgColor);

/**
 * @brief Draws a rectangle at the specified coordinates with the given dimensions, colors, and characters
 * 
 * @param x The X Coordinate
 * @param y The Y Coordinate
 * @param stroke The character to outline the rectangle
 * @param fill The character to fill the rectangle
 *  
 * @param width The width
 * @param height The height
 *
 * @param strokeFGColor The foreground color of the outline
 * @param strokeBGColor The background color of the outline
 * 
 * @param fillFGColor The foreground color of the fill
 * @param fillBGColor The background color of the fill
 * 
*/
void td_drawRect(int x, int y, unsigned int width, unsigned int height, char stroke, char fill, int strokeFGColor, int strokeBGColor, int fillFGColor, int fillBGColor);

// draw line

#ifdef __cplusplus
}
#endif


/**
 * Helper Functions
 * 
*/
#ifdef __cplusplus
extern "C" {
#endif


// unbuffered character input using termios.h
// char getch();

#ifdef __cplusplus
}
#endif