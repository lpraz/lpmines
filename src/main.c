/* Imports for C libraries */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Local imports */
#include "const.h"
#include "intops.h"

/* Declare functions TODO: move these outta hee */
void menu(int *psizex, int *psizey, int *pmines);
void custom(int *psizex, int *psizey, int *pmines);
void generate(int sizex, int sizey, int mines,
              int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
              int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]);
void parsemove(char in[], int sizex, int sizey,
               int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
               int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]);
void dig(int x, int y, int sizex, int sizey,
         int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
         int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]);
void digrec(int x, int y, int sizex, int sizey,
         int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
         int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]);
void split(char in[], int *x, int *y, char *action);
void showfield(int ground[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
               int surface[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
               int sizex, int sizey);
int finished(int sizex, int sizey,
             int ground[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
             int surface[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]);

/* Main method */
int main(void) {
    /* Board vars */
    int ground[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH];
    int surface[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH];
    int sizex, sizey, mines;
    int result;
    char in[INPUT_LENGTH];
    
    /* Intro menu; get difficulty */
    menu(&sizex, &sizey, &mines);
    
    /* Generate the playfield */
    generate(sizex, sizey, mines, &ground, &surface);
    
    /* Game loop */
    while (result = finished(sizex, sizey, ground, surface), !result) {
        /* Print field */
        showfield(ground, surface, sizex, sizey);
        
        /* Get input */
        printf("It's your move: "); /* MACINTOSH PLUS huehuehue */
        scanf("%s", in);
        
        /* Clear screen */
        printf("\033[2J");
        printf("\033[H");
        
        /* Use input */
        parsemove(in, sizex, sizey, &ground, &surface);
    }
    
    /* Show result */
    showfield(ground, surface, sizex, sizey);
    
    if (result == RESULT_CLEARED)
        printf("You cleared all the mines! Congratulations!\n");
    else if (result == RESULT_EXPLODED)
        printf("You uncovered a mine. Better luck next time...\n");
    
    return 0;
}

/* Difficulty menu */
void menu(int *psizex, int *psizey, int *pmines) {
    char input;
    
    do {
        /* Print messages */
        printf("(B)eginner/(I)ntermediate/(E)xpert/(C)ustom/(A)bout\n");
        printf("Select a difficulty (not case-sensitive): ");
        scanf("%c", &input);
        input = tolower(input);
        
        /* Declare board size */
        switch (input) {
            case 'b': /* Beginner */
                *psizex = BEGINNER_WIDTH;
                *psizey = BEGINNER_HEIGHT;
                *pmines = BEGINNER_MINES;
                printf("\033[2J\033[HStarted a new game on Beginner difficulty.\n");
                break;
            case 'i': /* Intermediate */
                *psizex = INTERMEDIATE_WIDTH;
                *psizey = INTERMEDIATE_HEIGHT;
                *pmines = INTERMEDIATE_MINES;
                printf("\033[2J\033[HStarted a new game on Intermediate difficulty.\n");
                break;
            case 'e': /* Expert */
                *psizex = EXPERT_WIDTH;
                *psizey = EXPERT_HEIGHT;
                *pmines = EXPERT_MINES;
                printf("\033[2J\033[HStarted a new game on Expert difficulty.\n");
                break;
            case 'c': /* Custom */
                custom(psizex, psizey, pmines);
                printf("\033[2J\033[HStarted a new custom game.\n");
                break;
            case 'a':
                printf("Beginner: %dx%d, %d mines\n",
                        BEGINNER_WIDTH,
                        BEGINNER_HEIGHT,
                        BEGINNER_MINES);
                printf("Intermediate: %dx%d, %d mines\n",
                        INTERMEDIATE_WIDTH,
                        INTERMEDIATE_HEIGHT,
                        INTERMEDIATE_MINES);
                printf("Expert: %dx%d, %d mines\n",
                        EXPERT_WIDTH,
                        EXPERT_HEIGHT,
                        EXPERT_MINES);
                printf("Custom: up to %dx%d, with up to %d mines\n",
                        MAX_CUSTOM_WIDTH,
                        MAX_CUSTOM_HEIGHT,
                        MAX_CUSTOM_MINES);
                break;
        }
    } while (input != 'b' && input != 'i' && input != 'e' && input != 'c');
}

/* Sets field size to custom values */
void custom(int *psizex, int *psizey, int *pmines) {
    *psizex = *psizey = *pmines = NO_INPUT_FLAG;
    
    while (*psizex > MAX_CUSTOM_WIDTH || *psizex < 1) {
        if (*psizex != NO_INPUT_FLAG)
            printf("%d is invalid! ", *psizex);

        printf("Choose a width from %d to %d: ", 1, MAX_CUSTOM_WIDTH);
        scanf("%d", psizex);
    }
    
    while (*psizey > MAX_CUSTOM_HEIGHT || *psizey < 1) {
        if (*psizey != NO_INPUT_FLAG)
            printf("%d is invalid!", *psizey);
        
        printf("Choose a height from %d to %d: ", 1, MAX_CUSTOM_HEIGHT);
        scanf("%d", psizey);
    }
    
    while (*pmines > MAX_CUSTOM_MINES || *pmines < 1) {
        if (*pmines != NO_INPUT_FLAG)
            printf("%d is invalid!", *pmines);
        
        printf("Choose a number of mines from %d to %d: ",
                1, MAX_CUSTOM_MINES);
        scanf("%d", pmines);
    }
}

/* Randomly generates a playfield. */
void generate(int sizex, int sizey, int mines,
              int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
              int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]) {
    int randx, randy;
    int near;
    
    /* Set RNG seed */
    srand(time(0));
    
    /* Make a clean playfield */
    for (int i = 0; i < MAX_CUSTOM_HEIGHT; i++) {
        for (int j = 0; j < MAX_CUSTOM_WIDTH; j++) {
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

/* Performs an in-game action based on input command */
void parsemove(char in[], int sizex, int sizey,
               int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
               int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]) {
    int x, y;
    char action;
    
    split(in, &x, &y, &action);
    
    if (x >= sizex || x < 0 || y > sizey || y < 0) {
        printf("That isn't a valid cell!\n");
        return;
    }
    
    switch (action) {
        case 'd': /* Dig */
            dig(x, y, sizex, sizey, ground, surface);
            break;
        case 'p': /* Place flag */
            if ((*surface)[y][x] == HIDDEN) {
                printf("Placed flag at (%d, %d).\n", x + 1, y + 1);
                (*surface)[y][x] = FLAGGED;
            } else if ((*surface)[y][x] == FLAGGED) {
                printf("(%d, %d) is already flagged!\n", x + 1, y + 1); 
            } else if ((*surface)[y][x] == REVEALED) {
                printf("(%d, %d) is exposed!\n", x + 1, y + 1);
            }
            break;
        case 'r': /* Remove flag */
            if ((*surface)[y][x] == FLAGGED) {
                printf("Removed flag at (%d, %d).\n", x + 1, y + 1);
                (*surface)[y][x] = HIDDEN;
            } else if ((*surface)[y][x] == HIDDEN) {
                printf("(%d, %d) has no flag!\n", x + 1, y + 1);
            } else if ((*surface)[y][x] == REVEALED) {
                printf("(%d, %d) is exposed!\n", x + 1, y + 1);
            }
            break;
        default: /* Invalid input */
            printf("That isn't a valid action!\n");
            break;
    }
}

/* Digs a square on the field. If a mine is uncovered, returns the
 * result.
 */
void dig(int x, int y, int sizex, int sizey,
         int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
         int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]) {
    if ((*surface)[y][x] == HIDDEN) {
        printf("Dug at (%d, %d).\n", x + 1, y + 1);
        
        digrec(x, y, sizex, sizey, ground, surface);
    } else if ((*surface)[y][x] == REVEALED) {
        printf("(%d, %d) is already exposed!\n", x + 1, y + 1);
    } else if ((*surface)[y][x] == FLAGGED) {
        printf("(%d, %d) is flagged!\n", x + 1, y + 1);
    }
}

/* Digs the square specified, and all other continguous squares
 * without mines.
 */
void digrec(int x, int y, int sizex, int sizey,
            int (*ground)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
            int (*surface)[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]) {
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

/* Splits in-game action command into coordinate and action */
void split(char in[], int *x, int *y, char *action) {
    char *temp;
    
    temp = strtok(in, COMMAND_TOKENS);
    if (temp != NULL)
        *x = atoi(temp) - 1;
    
    temp = strtok(NULL, COMMAND_TOKENS);
    if (temp != NULL)
        *y = atoi(temp) - 1;
    
    temp = strtok(NULL, COMMAND_TOKENS);
    if (temp != NULL)
        *action = *temp;
}

/* Prints the field */
void showfield(int ground[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
               int surface[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
               int sizex, int sizey) {
    /* Declaraions */
    int curdigit;
    
    /* Print column numbers */
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

int finished(int sizex, int sizey,
             int ground[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH],
             int surface[MAX_CUSTOM_HEIGHT][MAX_CUSTOM_WIDTH]) {
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
