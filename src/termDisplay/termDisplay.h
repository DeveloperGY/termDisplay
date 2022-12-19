#pragma once

extern int TD_WIDTH;
extern int TD_HEIGHT;

extern char **TD_BUFFER;

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
