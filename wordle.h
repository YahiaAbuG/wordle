#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 10
#define MIN_WORD_LENGTH 2

int processFile(char *, char ***, int *);
char **allocateSpace(char **, int);
void displayRules();
int chooseWord(int);
bool checkGuess(char *, char *);
void printWord(char *, char *);