/*
 *  const.h
 *  Provides constants used by more than one source file. Constants
 *  used by only one source file can be found in their respective
 *  headers.
 */

#ifndef CONST_H
#define CONST_H

/* Cell surface state */
#define HIDDEN 1
#define REVEALED 2
#define FLAGGED 3

/* Cell ground state */
#define EMPTY -2
#define HAS_MINE -1

/* Maximum playfield params */
#define MAX_WIDTH 30
#define MAX_HEIGHT 20
#define MAX_MINES 150

/* Results */
#define NOT_FINISHED 0
#define RESULT_EXPLODED 2
#define RESULT_CLEARED 1

#endif
