#include "wordle.h"

int main(int argc, char *argv[])
{

    char **listArray = NULL;
    char *word, *guess = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH + 1);
    char again = 'y';
    int wordCount = 0, help = 0, tries = 0;
    int status, choice, length;
    bool check = false, inList = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'h')
            {
                help = 1;
            }
            else
            {
                printf("Invalid option\n");
            }
        }
        else
        {
            status = processFile(argv[i], &listArray, &wordCount);
            if (status == -1)
            {
                printf("Invalid filename (argument %d)\n", i);
            }
        }
    }

    if (listArray == NULL)
    {

        printf("No data processed\n\n");
        printf("Usage:\n");
        printf("%s <file> [-h] [ <file> ...]\n", argv[0]);

        printf("Use -h if you would like the rules of the game to be displayed for you before you play.\n");

        return -1;
    }

    printf("Welcome to Wordle!\n");

    if (help == 1)
    {
        displayRules();
    }

    while (tolower(again) == 'y')
    {

        tries = 0;
        check = false;

        choice = chooseWord(wordCount);
        word = listArray[choice];
        length = strlen(word);

        printf("A word has been chosen. Its length is %d.\n", length);

        while (tries < 6 && !check)
        {

            do
            {

                inList = false;

                printf("\nEnter your guess:");
                scanf("%s", guess);

                for (int i = 0; i < strlen(guess); i++)
                {
                    guess[i] = tolower(guess[i]);
                }

                for (int i = 0; i < wordCount; i++)
                {
                    if (strcmp(guess, listArray[i]) == 0)
                    {
                        inList = true;
                    }
                }

                if (strlen(guess) != length)
                {
                    printf("Invalid word length. Enter a word of size %d\n", length);
                }
                else if (!inList)
                {
                    printf("Word not in word list\n");
                }
            } while (!inList || strlen(guess) != length);
            tries++;

            check = checkGuess(guess, word);
        }

        if (check)
        {
            printf("\nCongrats! You guessed the word in %d tries!\n", tries);
        }
        else
        {
            printf("\nYou lost! The word was:\n");
            printWord(word, NULL);
        }

        printf("Would you like to play again? (y/N): ");
        scanf(" %c", &again);
    }

    free(guess);

    for (int i = 0; i < wordCount; i++)
    {
        free(listArray[i]);
    }

    free(listArray);

    return 0;
}