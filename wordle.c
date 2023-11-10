#include "wordle.h"

int processFile(char *filename, char ***arr, int *currentSize)
{

    FILE *fp = fopen(filename, "r");
    char *word = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH + 1);
    int wordCount = 0;

    if (fp == NULL)
    {
        return -1;
    }

    while (fgets(word, MAX_WORD_LENGTH + 1, fp) != NULL)
    {

        if (wordCount >= *currentSize)
        {

            *arr = allocateSpace(*arr, *currentSize);
            (*currentSize)++;
        }

        word[strlen(word) - 1] = '\0';
        strcpy((*arr)[wordCount], word);
        wordCount++;
    }

    printf("%d words processed\n\n", wordCount);

    free(word);

    fclose(fp);

    return 1;
}

char **allocateSpace(char **arr, int wordCount)
{

    if (arr == NULL)
    {
        arr = (char **)malloc(sizeof(char *));
        arr[wordCount] = (char *)malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
    }
    else
    {
        arr = (char **)realloc(arr, sizeof(char *) * (wordCount + 1));
        arr[wordCount] = (char *)malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
    }

    return arr;
}

void displayRules()
{
    printf("\n\e[1mHow to Play:\e[m\n\n");
    printf("Guess the Wordle in 6 tries.\n\n");
    printf("Each guess must be a valid word.\n\n");
    printf("\e[1mExamples:\e[m\n\n");
    printf("When a letter is \e[1;32mGREEN\e[m, it is in the correct spot.\n");
    printf("\e[1;32mW\e[m E A R Y\n");
    printf("When a letter is \e[1;33mYELLOW\e[m, it is in the word, but not in the right spot.\n");
    printf("P \e[1;33mI\e[m L L S\n");
    printf("When a letter is WHITE, it is not in the word.\n");
    printf("V A G U E\n\n");
}

int chooseWord(int wordCount)
{

    srand(time(NULL));

    return (rand() % wordCount) + 1;
}

bool checkGuess(char *guess, char *word)
{
    int len = strlen(word);
    char colours[len];
    bool used[len];

    for (int i = 0; i < len; i++)
    {
        colours[i] = 'B';
        used[i] = false;
    }

    for (int i = 0; i < len; i++)
    {
        if (guess[i] == word[i])
        {
            colours[i] = 'G';
            used[i] = true;
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (colours[i] == 'B')
        {
            for (int j = 0; j < len; j++)
            {
                if ((guess[i] == word[j]) && !used[j])
                {
                    colours[i] = 'Y';
                    used[j] = true;
                    break;
                }
            }
        }
    }

    printWord(guess, colours);

    if (strcmp(word, guess) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printWord(char *word, char *colours)
{

    char letter;

    if (colours != NULL)
    {

        for (int i = 0; i < strlen(word); i++)
        {

            letter = word[i];

            if (colours[i] == 'G')
            {

                printf(" \e[32m%c\e[m ", toupper(letter));
            }
            else if (colours[i] == 'Y')
            {

                printf(" \e[33m%c\e[m ", toupper(letter));
            }
            else
            {

                printf(" %c ", toupper(letter));
            }
        }
    }
    else {
        for (int i = 0; i<strlen(word); i++) {
            letter = word[i];
            printf(" %c ", toupper(letter));
        }
    }
    printf("\n");
}