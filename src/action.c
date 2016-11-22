/*
 * action.c
 * Provides functions related to manipulation of the playfield by the
 * player in a game.
 */

/* Import self */
#include "action.h"

/* Local imports */
#include "const.h"

/* Stdlib imports */
#include <stdio.h>

/* Performs an in-game action based on a command. */
void parsemove(int x, int y, char action, int sizex, int sizey,
               int (*ground)[MAX_HEIGHT][MAX_WIDTH],
               int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    /* Check if cell location is valid */
    if (x >= sizex || x < 0 || y > sizey || y < 0) {
        printf("That isn't a valid cell!");
        return;
    }
    
    /* Perform the action */
    switch(action) {
        case 'd': /* Dig */
            dig(x, y, sizex, sizey, ground, surface);
            break;
        case 'p': /* Place flag */
            pflag(x, y, ground, surface);
            break;
        case 'r': /* Remove flag */
            rflag(x, y, ground, surface);
            break;
        default: /* Anything else */
            printf("That isn't a valid action!\n");
            break;
    }
}

/* Checks if a cell on the field is diggable. If so, digs it. */
void dig(int x, int y, int sizex, int sizey,
         int (*ground)[MAX_HEIGHT][MAX_WIDTH],
         int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    if ((*surface)[y][x] == HIDDEN) {
        printf("Dug at (%d, %d).\n", x + 1, y + 1);
        digrec(x, y, sizex, sizey, ground, surface);
    } else if ((*surface)[y][x] == REVEALED) {
        printf("(%d, %d) is already exposed!\n", x + 1, y + 1);
    } else if ((*surface)[y][x] == FLAGGED) {
        printf("(%d, %d) is flagged!\n", x + 1, y + 1);
    }
}

/* Digs a cell, and if it is empty, digs all those around it until it
 * reaches the edge of the playfield or a non-empty cell.
 */
void digrec(int x, int y, int sizex, int sizey,
            int (*ground)[MAX_HEIGHT][MAX_WIDTH],
            int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    (*surface)[y][x] = REVEALED;
    
    if ((*ground)[y][x] == EMPTY)
        for (int i = (((y - 1) < 0) ? 0 : (y - 1));
             i < (((y + 1) > sizey) ? sizey : (y + 2));
             i++)
            for (int j = (((x - 1) < 0) ? 0 : (x - 1));
                 j < (((x + 1) > sizex) ? sizex : (x + 2));
                 j++)
                if ((*surface)[i][j] == HIDDEN)
                    digrec(j, i, sizex, sizey, ground, surface);

}

/* Checks if a cell on the field can have a flag placed on it. If so
 * places it. */
void pflag(int x, int y,
           int (*ground)[MAX_HEIGHT][MAX_WIDTH],
           int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    if ((*surface)[y][x] == FLAGGED) {
         printf("Removed flag at (%d, %d).\n", x + 1, y + 1);
        (*surface)[y][x] = HIDDEN;
    } else if ((*surface)[y][x] == HIDDEN) {
        printf("(%d, %d) has no flag!\n", x + 1, y + 1);
    } else if ((*surface)[y][x] == REVEALED) {
        printf("(%d, %d) is exposed!\n", x + 1, y + 1);
    }
}

/* Checks if a cell on the field can have a flag removed from it. If
 * so, removes it. */
void rflag(int x, int y,
           int (*ground)[MAX_HEIGHT][MAX_WIDTH],
           int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    if ((*surface)[y][x] == FLAGGED) {
        printf("Removed flag at (%d, %d).\n", x + 1, y + 1);
        (*surface)[y][x] = HIDDEN;
    } else if ((*surface)[y][x] == HIDDEN) {
        printf("(%d, %d) has no flag!\n", x + 1, y + 1);
    } else if ((*surface)[y][x] == REVEALED) {
        printf("(%d, %d) is exposed!\n", x + 1, y + 1);
    }
}
