/*
 * input.c
 * Provides functions for getting input from the user at
 * runtime, including menus for selecting a playfield size and prompts
 * for user action during gameplay.
 */

/* Import self */
#include "input.h"

/* Local imports */
#include "const.h"

/* Stdlib imports */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Parses command-line arguments, returns whether the game should
 * proceed.
 */
/* TODO: Process playfield params */
bool args(int argc, char *argv[], int *psizex, int *psizey, int *pmines,
          bool *color) {
    char *temp;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--monochrome") == 0) {
            *color = false;
        } else if (strcmp(argv[i], "--version") == 0) {
            printf("lpmines\n");
            return false;
        } else if (strcmp(argv[i], "--beginner") == 0) {
            *psizex = BEGINNER_WIDTH;
            *psizey = BEGINNER_HEIGHT;
            *pmines = BEGINNER_MINES;
        } else if (strcmp(argv[i], "--intermediate") == 0) {
            *psizex = INTERMEDIATE_WIDTH;
            *psizey = INTERMEDIATE_HEIGHT;
            *pmines = INTERMEDIATE_MINES;
        } else if (strcmp(argv[i], "--expert") == 0) {
            *psizex = EXPERT_WIDTH;
            *psizey = EXPERT_HEIGHT;
            *pmines = EXPERT_MINES;
        } else if (strncmp(argv[i], "--width=", 8) == 0) {
            temp = malloc((strlen(argv[i]) - 8) * sizeof(char));
            strcpy(temp, argv[i] + 8);
            *psizex = atoi(temp);
        } else if (strncmp(argv[i], "--height=", 9) == 0) {
            temp = malloc((strlen(argv[i]) - 9) * sizeof(char));
            strcpy(temp, argv[i] + 9);
            *psizey = atoi(temp);
        } else if (strncmp(argv[i], "--mines=", 8) == 0) {
            temp = malloc((strlen(argv[i]) - 8) * sizeof(char));
            strcpy(temp, argv[i] + 8);
            *pmines = atoi(temp);
        } else if (argv[i][0] == '-') {
            for (int j = 0; j < strlen(argv[i]); j++) {
                switch (argv[i][j]) {
                    case 'm':
                        *color = false;
                        break;
                    case 'b':
                        *psizex = BEGINNER_WIDTH;
                        *psizey = BEGINNER_HEIGHT;
                        *pmines = BEGINNER_MINES;
                        break;
                    case 'i':
                        *psizex = INTERMEDIATE_WIDTH;
                        *psizey = INTERMEDIATE_HEIGHT;
                        *pmines = INTERMEDIATE_MINES;
                        break;
                    case 'e':
                        *psizex = EXPERT_WIDTH;
                        *psizey = EXPERT_HEIGHT;
                        *pmines = EXPERT_MINES;
                        break;
                }
            }
        }
    }
    
    return true;
}

/* Provides the main menu, allowing the user to select a difficulty. */
void menu(int *psizex, int *psizey, int *pmines) {
    char in;
    
    if (*psizex == NO_INPUT_FLAG &&
        *psizey == NO_INPUT_FLAG &&
        *pmines == NO_INPUT_FLAG) {
        do {
            /* Print messages */
            printf("(B)eginner/(I)ntermediate/(E)xpert/(C)ustom/(A)bout\n");
            printf("Select a difficulty (not case-sensitive): ");
            scanf("%c", &in);
            in = tolower(in);
            
            /* Declare board size */
            switch (in) {
                case 'b': /* Beginner */
                    *psizex = BEGINNER_WIDTH;
                    *psizey = BEGINNER_HEIGHT;
                    *pmines = BEGINNER_MINES;
                    printf("\033[2J\033[H");
                    printf("Started a new game on Beginner difficulty.\n");
                    break;
                case 'i': /* Intermediate */
                    *psizex = INTERMEDIATE_WIDTH;
                    *psizey = INTERMEDIATE_HEIGHT;
                    *pmines = INTERMEDIATE_MINES;
                    printf("\033[2J\033[H");
                    printf("Started a new game on Intermediate difficulty.\n");
                    break;
                case 'e': /* Expert */
                    *psizex = EXPERT_WIDTH;
                    *psizey = EXPERT_HEIGHT;
                    *pmines = EXPERT_MINES;
                    printf("\033[2J\033[H");
                    printf("Started a new game on Expert difficulty.\n");
                    break;
                case 'c': /* Custom */
                    custom(psizex, psizey, pmines);
                    printf("\033[2J\033[H");
                    printf("Started a new custom game.\n");
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
                            MAX_WIDTH,
                            MAX_HEIGHT,
                            MAX_MINES);
                    break;
            }
        } while (in != 'b' && in != 'i' && in != 'e' && in != 'c');
    } else if (*psizex == NO_INPUT_FLAG ||
               *psizey == NO_INPUT_FLAG ||
               *pmines == NO_INPUT_FLAG) {
        custom(psizex, psizey, pmines);
        printf("\033[2J\033[H");
        printf("Started a new custom game.\n");
    } else {
        printf("\033[2J\033[H");
        printf("Started a new game.\n");
    }
}

/* Lets the user define a custom playfield. */
void custom(int *psizex, int *psizey, int *pmines) {
    while (*psizex > MAX_WIDTH || *psizex < 1) {
        if (*psizex != NO_INPUT_FLAG)
            printf("%d is invalid! ", *psizex);

        printf("Choose a width from %d to %d: ", 1, MAX_WIDTH);
        scanf("%d", psizex);
    }
    
    while (*psizey > MAX_HEIGHT || *psizey < 1) {
        if (*psizey != NO_INPUT_FLAG)
            printf("%d is invalid!", *psizey);
        
        printf("Choose a height from %d to %d: ", 1, MAX_HEIGHT);
        scanf("%d", psizey);
    }
    
    while (*pmines > MAX_MINES || *pmines < 1) {
        if (*pmines != NO_INPUT_FLAG)
            printf("%d is invalid!", *pmines);
        
        printf("Choose a number of mines from %d to %d: ",
                1, MAX_MINES);
        scanf("%d", pmines);
    }
}

/* Splits a user's command (as string) into a pair of x/y coordinates
 * and a char.
 */
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
