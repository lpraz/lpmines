/*
 * field.c
 * Provides functions related to the playfield.
 */

/* Import self */
#include "field.h"

/* Local imports */
#include "const.h"
#include "intops.h"

/* Stdlib imports */
#include <stdio.h>
#include <time.h>

/* Randomly generates a playfield. */
void generate(int sizex, int sizey, int mines,
              int (*ground)[MAX_HEIGHT][MAX_WIDTH],
              int (*surface)[MAX_HEIGHT][MAX_WIDTH]) {
    int randx, randy;
    int near;
    
    /* Set RNG seed */
    srand(time(0));
    
    /* Make a clean playfield */
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            (*ground)[i][j] = EMPTY;
            if (i < sizey && j < sizex)
                (*surface)[i][j] = HIDDEN;
            else
                (*surface)[i][j] = REVEALED;
        }
    }
    
    /* Place mines */
    while (mines > 0) {
        randx = rand() % sizex;
        randy = rand() % sizey;
        
        if ((*ground)[randy][randx] != HAS_MINE) {
            (*ground)[randy][randx] = HAS_MINE;
            --mines;
        }
    }
    
    /* Generate "how many mines near?" nums */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if ((*ground)[i][j] != HAS_MINE) {
                near = 0;
                
                for (int k = (((i - 1) > 0) ? (i - 1) : 0);
                     k < (((i + 1) > sizey) ? sizey : (i + 2));
                     k++) {
                    for (int l = (((j - 1) > 0) ? (j - 1) : 0);
                         l < (((j + 1) > sizex) ? sizex : (j + 2));
                         l++) {
                        if ((*ground)[k][l] == HAS_MINE)
                            near++;
                     }
                }
                
                if (near != 0)
                    (*ground)[i][j] = near;
            }
        }
    }
}

/* Draws the playfield to the terminal. */
void drawfield(int sizex, int sizey,
               int ground[MAX_HEIGHT][MAX_WIDTH],
               int surface[MAX_HEIGHT][MAX_WIDTH]) {
    /* Print column numbers */
    drawcolnums(sizex, sizey);

    for (int i = 0; i < sizey; i++) {
        /* Print row numbers */
        printf("%*d ", numlength(sizey), i + 1);
        
        for (int j = 0; j < sizex; j++) {
            /* Print contents of each cell */
            switch(surface[i][j]) {
                case HIDDEN:
                    printf(" .");
                    break;
                case REVEALED:
                    switch(ground[i][j]) {
                        case EMPTY:
                            printf(" _");
                            break;
                        case HAS_MINE:
                            printf(" X");
                            break;
                        default:
                            printf(" %d", ground[i][j]);
                            break;
                    }
                    break;
                case FLAGGED:
                    printf(" F");
                    break;
                default:
                    printf(" ?");
                    break;
            }
        }
        printf("\n");
    }    
}

/* Draws column numbers (written vertically) for the playfield. */
void drawcolnums(int sizex, int sizey) {
    int curdigit;

    for (int i = numlength(sizex); i > 0; i--) {
        printf("%*s ", numlength(sizey), " ");
        for (int j = 0; j < sizex; j++) {
            curdigit = digitat(j + 1, i);
            if (curdigit == 0 && j + 1 < powint(BASE, i - 1))
                printf("  ");
            else
                printf(" %d", curdigit);
        }
        printf("\n");
    }
}

/* Checks if the field has been completely swept, or if a mine has been
 * revealed.
 */
int finished(int sizex, int sizey,
             int ground[MAX_HEIGHT][MAX_WIDTH],
             int surface[MAX_HEIGHT][MAX_WIDTH]) {
    /* Check for exposed mines */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if (ground[i][j] == HAS_MINE && surface[i][j] == REVEALED)
                return RESULT_EXPLODED;
        }
    }
    
    /* Check if revealed everything */
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            if (surface[i][j] != REVEALED && ground[i][j] != HAS_MINE)
                return NOT_FINISHED;
        }
    }
    
    return RESULT_CLEARED;
}
