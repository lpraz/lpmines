#include <ctype.h>
#include <stdio.h>

/* Magic numbers: field cell state */
#define HIDDEN 0
#define REVEALED 1
#define FLAGGED 2

/* Magic numbers: difficulty/field dimensions */
#define BEGINNER_WIDTH 10
#define BEGINNER_HEIGHT 10
#define INTERMEDIATE_WIDTH 20
#define INTERMEDIATE_HEIGHT 20
#define EXPERT_WIDTH 40
#define EXPERT_HEIGHT 25
#define MAX_CUSTOM_WIDTH 50
#define MAX_CUSTOM_HEIGHT 30

/* Main method */
int main(void) {
    /* Board vars */
    int ground[100][100];
    int surface[100][100];
    int sizex, sizey;
    
    /* Intro menu; get difficulty */
    menu(&sizex, &sizey);
    
    /* Game loop */
    while (/* Not all safe tiles uncovered, no mines uncovered */) {
        /* Print field */
        showfield(ground, surface, sizex, sizey);
        
        /* Get input */
        printf("It's your move: "); /* MACINTOSH PLUS huehuehue */
        parsemove(gets());
    }
    
    return 0;
}

/* Difficulty menu */
void menu(int *psizex, int *psizey) {
    char input;
    
    do {
        /* Print messages */
        printf("Welcome to Minesweeper!\n");
        printf("(B)eginner/(I)ntermediate/(E)xpert/(C)ustom/(A)bout\n");
        printf("Select a difficulty (not case-sensitive): ");
        input = tolower(getchar());
        
        /* Declare board size */
        switch (input) {
            case 'b': /* Beginner */
                *psizex = 10;
                *psizey = 10;
                break;
            case 'i': /* Intermediate */
                *psizex = 20;
                *psizey = 20;
                break;
            case 'e': /* Advanced */
                *psizex = 40;
                *psizey = 25;
                break;
            case 'c': /* Custom */
                custom(*psizex, *psizey);
            case 'a':
                printf("Beginner: 10x10\n");
                printf("Intermediate: 20x20\n");
                printf("Expert: 40x25\n");
                break;
        }
    } while (input != 'b' && input != 'i' && input != 'e');
}

/* Sets field size to custom values */
void custom(int *psizex, int *psizey) {
    
}

/* Parses an in-game action with code x:y:a */
void parsemove(char[] in) {
    int x, y;
    char action;
    switch (action) {
        case 'd' /* Dig */
        case 'p' /* Place flag */
            if (*surface[y][x] == HIDDEN) {
                printf("Placed flag at (%d, %d).\n", x, y)
                *surface[y][x] = FLAGGED;
            } else if (*surface[y][x] == FLAGGED) {
                printf("The cell at (%d, %d) is already flagged!\n", x, y);
            } else if (*surface[y][x] == REVEALED) {
                printf("The cell at (%d, %d) is already exposed!\n", x, y);
            }
            break;
        case 'r' /* Remove flag */
            if (*surface[y][x] == FLAGGED) {
                printf("Removed flag at (%d, %d).\n", x, y)
                *surface[y][x] == HIDDEN;
            } else if (*surface[y][x] == HIDDEN) {
                printf("The cell at (%d, %d) has no flag!\n", x, y);
            } else if (*surface[y][x] == REVEALED) {
                printf("The cell at (%d, %d) is already exposed!\n", x, y);
            }
            break;
    }
}

/* Prints the field */
void showfield(int ground[][], int surface[][], int sizex, int sizey) {
    /* Print column numbers */
    for (int i = 0; i < numlength(sizex); i++) {
        printf("%*s ", numlength(sizey), "");
        for (int j = 0; j < sizex; j++) {
            int curdigit = ((j + 1) / (10 * i)) % 10;
            if (curdigit == 0)
                printf("  ");
            else
                printf("%d ", (j + 1) / (10 * i) % 10);
        }
    }

    for (int i = 0; i < sizey; i++) {
        /* Print row numbers */
        printf("%*d ", numlength(sizey), i + 1);
        
        for (int j = 0; j < sizex; j++) {
            /* Print contents of each cell */
            select(surface[i][j]) {
                case HIDDEN:
                    printf(" .");
                case REVEALED:
                    printf(" %d", ground[i][j]);
                case FLAGGED:
                    printf(" F");
            }
        }
        printf("\n\n");
    }
}

/* Gives digits in an integer */
int numlength(int num) {
    int len;
    for (len = 0; num % 10 > 0; len++)
        num /= 10;
    
    return len;
}
