#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

extern int TD_WIDTH;
extern int TD_HEIGHT;

extern char **TD_BUFFER;

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
 */
void td_drawPoint(int x, int y, char c);

#ifdef __cplusplus
}
#endif
