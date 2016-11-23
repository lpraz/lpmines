/*
 * field.h
 * Defines abstract functions related to the playfield.
 */

#ifndef FIELD_H
#define FIELD_H

/* Local imports */
#include "const.h"

/* Stdlib imports */
#include <stdbool.h>

/* Constants - colours */
#define COL_NUM_COLOR "\033[40;93m"
#define ROW_NUM_COLOR "\033[40;93m"
#define HIDDEN_COLOR "\033[0m"
#define EMPTY_COLOR "\033[0m"
#define FLAG_COLOR "\033[40;91m"
#define MINE_COLOR "\033[41;37m"

#define ONE_COLOR "\033[40;34m"
#define TWO_COLOR "\033[40;32m"
#define THREE_COLOR "\033[40;31m"
#define FOUR_COLOR "\033[40;33m"
#define FIVE_COLOR "\033[40;94m"
#define SIX_COLOR "\033[40;92m"
#define SEVEN_COLOR "\033[40;91m"
#define EIGHT_COLOR "\033[40;93m"

/* Randomly generates a playfield. */
void generate(int sizex, int sizey, int mines,
              int (*ground)[MAX_HEIGHT][MAX_WIDTH],
              int (*surface)[MAX_HEIGHT][MAX_WIDTH]);

/* Draws the playfield to the terminal. */
void drawfield(int sizex, int sizey, bool color,
               int ground[MAX_HEIGHT][MAX_WIDTH],
               int surface[MAX_HEIGHT][MAX_WIDTH]);

/* Draws column numbers (written vertically) for the playfield. */
void drawcolnums(int sizex, int sizey);

/* Checks if the field has been completely swept. */
int finished(int sizex, int sizey,
             int ground[MAX_HEIGHT][MAX_WIDTH],
             int surface[MAX_HEIGHT][MAX_WIDTH]);

#endif
