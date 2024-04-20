#define _CRT_SECURE_NO_WARNINGS /* disable security warnings in Microsoft Visual Studio */
#include <stdio.h>
#include <stdlib.h>

#define S1LENGTH 40
#define S2LENGTHMIN 2
#define S2LENGTHMAX 20

char* generateS1();
char* generateS2();
char getReplacementCharacter();
void strfilter(char* s1, char* s2, char ch);

int isUpperCaseLetter(int iochar);
char* createDuplicateArray(char* original);

int main(void) {
    printf("Welcome User\n");
    char selection = 'Y';
    int invalidSelectionFlag;

    /* Generate a random pattern of uppercase letters only once */
    char* original = generateS1();

    while (selection == 'Y' || selection == 'y') {
        /* Reset invalidSelectionFlag */
        invalidSelectionFlag = 0;

        /* Generate a pointer, that will be a copy of the randomly generated array, called s1 */
        char* s1 = createDuplicateArray(original);

        /* Get user string of uppercase letters */
        char* s2;

        do {
            s2 = generateS2(); /* Loop until we have a valid string */
        } while (*s2 == '\0');

        /* Get replacement character from user */
        char ch;

        do {
            ch = getReplacementCharacter(); /* Loop until we have a single valid character */
        } while (ch == '\0');

        /*  Search s1 and replaces any occurrences of any of the characters contained in s2 with character ch */
        strfilter(s1, s2, ch);

        /* Print the original string, user string, user char, and filtered string */
        printf("\ns1 = ");
        puts(original);

        printf("s2 = ");
        puts(s2);

        printf("ch = '%c'\n", ch);

        printf("s3 = ");
        puts(s1);

        /* Prompt the user the restart the program */
        do {
            printf("\nWould you like to run the program again? Type 'Y' for Yes, enter 'N' to exit\n");
            selection = getchar();

            /* If we encounter more than one character, it's automatically invalid */
            if (getchar() != '\n') {
                while (getchar() != '\n') {}
                invalidSelectionFlag = 1;
            }
            else {
                /* If the single character isn't Y or N, it is invalid */
                if (selection != 'Y' && selection != 'y' && selection != 'N' && selection != 'n') {
                    invalidSelectionFlag = 1;
                }
                else {
                    invalidSelectionFlag = 0; /* We must reset flag here in case of multiple consecutive invalid inputs */
                }
            }

            if (invalidSelectionFlag) {
                printf("Error: Invalid selection\n");
            }
        } while (invalidSelectionFlag);
    }

    printf("\nTerminating Program..\n");
    return 0;
}

char* generateS1() {
    int rand_num;

    /* Create a pointer to an array of characters */
    static char s1[S1LENGTH + 1];
    char* ptr = s1;

        for (int i = 0; i < S1LENGTH; ++i) {
            /* Generate random number between 1 and 26 */
            rand_num = rand() % 26;

            /* Shift the range to 65-90, cast to char, and increment pointer */
            *ptr++ = (char)(rand_num + 65);
        }

    /* Null-terminating string */
    *ptr = '\0';

    return s1;
}

char* generateS2() {
    /* Get the user string */
    printf("\nEnter a string of uppercase letters 'A' - 'Z'\n");
    printf("Must contain between %d and %d characters: ", S2LENGTHMIN, S2LENGTHMAX);

    int numCharacters = 0; /* Keep track of num characters */
    int invalidCharacterDetected = 0; /* Flag to keep track of valid characters */
    int hasExceededCharacterLimit = 0; /* Flag to keep track of string length */
    char currentCharacter; /* Keep track of current character being processed */

    static char s2[S2LENGTHMAX + 1]; /* Create a static array */
    char* s2ptr = s2; /* Use a pointer to traverse the array */

    /* Process input while:
    /* 1. There are still characters in the input buffer,
    /* 2. We haven't encountered an invalid character, AND
    /* 3. The number of characters does not exceed the S2LENGTHMAX limit */
    while ((currentCharacter = getchar()) != EOF && currentCharacter != '\n') {
        ++numCharacters; /* Increment character count */

        /* If we've already encountered an invalid character, simply increment the character counter */
        if (!invalidCharacterDetected) {
            /* Now we check to see if we've exceeded the character limit */
            hasExceededCharacterLimit = (numCharacters > S2LENGTHMAX);

            if (!hasExceededCharacterLimit) {
                /* Finally, we check for invalid character */
                if (isUpperCaseLetter(currentCharacter)) {
                    *s2ptr++ = currentCharacter;
                }
                else {
                    invalidCharacterDetected = 1;
                }
            }
        }
    }

    /* Check if user input meets min string length requirement */
    int isLessThanRequiredLength = (numCharacters < S2LENGTHMIN);

    /* Print appropriate error messages */
    if (invalidCharacterDetected) {
        printf("Error: Invalid characters detected. Input must contain ONLY uppercase alphabetical characters\n");
    }

    if (hasExceededCharacterLimit || isLessThanRequiredLength) {
        printf("Error: Invalid string length. Input must be between %d and %d characters long\n", S2LENGTHMIN, S2LENGTHMAX);
    }

    /* If any of the error flags were raised, set the first index of the array to the null terminating character */
    if (invalidCharacterDetected || hasExceededCharacterLimit || isLessThanRequiredLength) {
        *s2 = '\0';
    }
    else {
        *s2ptr = '\0';
    }

    return s2;
}

/* Prompts the user to enter a single character. Returns null termianting character upon failure. */
char getReplacementCharacter() {
    printf("\nEnter a single replacement character: ");
    int numCharacters = 0;
    int errorFlag = 0;

    /* Read a single character from input */
    char iochar = getchar();

    /* If there are additional characters in the input buffer, clear the input buffer and raise error flag */
    if (getchar() != '\n') {
        while (getchar() != '\n') {}
        errorFlag = 1;
    }

    if (errorFlag) {
        printf("Error: Multiple characters detected. Only single characters will be accepted.\n");
        iochar = '\0';
    }

    return iochar;
}

void strfilter(char* s1, char* s2, char ch) {
    char* originalS1 = s1;  /* Store the original pointer to reset later */

    while (*s2 != '\0') {
        s1 = originalS1;  /* Reset s1 pointer for each character in s2 */
        while (*s1 != '\0') {
            if (*s1 == *s2) {
                *s1 = ch;
            }
            s1++;
        }
        s2++;
    }
}

int isUpperCaseLetter(int iochar) {
    return (iochar >= 'A' && iochar <= 'Z');
}

/* Returns a pointer to an array of characters identical to the parameter */
char* createDuplicateArray(char* original) {
    static char duplicate[S1LENGTH + 1];
    char* duplicatePtr = duplicate;

    for (int i = 0; i < S1LENGTH; ++i) {
        *duplicatePtr++ = *original++;
    }

    *duplicatePtr = '\0'; /* Null-terminate the duplicate array to indicate end of string */
    return duplicate;
}

/* TEST CASES */
/*
1. User enters single lowercase char
2. User enters single uppercase char
3. User enters all uppercase chars, exceeds max limit (>20)
4. User enters all lowercase chars, exceeds max limit
5. User enters mix of upper/lowercase chars, exceeds max limit
6. User enters mix of upper/lowercase chars, within limit (2-20)
7. User enters non-alphabetical characters
8. User enters max possible characters

9. Replacement char is more than one chararacter long

10. User enters string when prompted to repeat program
11. User enters invalid single char when prompted to repeat program
12. User enters lowercase 'y' to repeat program
*/