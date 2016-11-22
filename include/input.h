/*
 * input.h
 * Defines abstract functions for getting input from the user at
 * runtime, including menus for selecting a playfield size and prompts
 * for user action during gameplay.
 */

#ifndef INPUT_H
#define INPUT_H

/* Constants */
#define BEGINNER_WIDTH 10
#define BEGINNER_HEIGHT 10
#define BEGINNER_MINES 10

#define INTERMEDIATE_WIDTH 20
#define INTERMEDIATE_HEIGHT 20
#define INTERMEDIATE_MINES 40

#define EXPERT_WIDTH 30
#define EXPERT_HEIGHT 20
#define EXPERT_MINES 90

#define INPUT_LENGTH 10
#define NO_INPUT_FLAG -1
#define COMMAND_TOKENS ".,;:"

/* Provides the main menu, allowing the user to select a difficulty. */
void menu(int *psizex, int *psizey, int *pmines);

/* Lets the user define a custom playfield. */
void custom(int *psizex, int *psizey, int *pmines);

/* Splits a user's command (as string) into a pair of x/y coordinates
 * and a char.
 */
void split(char in[], int *x, int *y, char *action);

#endif
