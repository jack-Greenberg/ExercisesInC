/* cards.c - Card counting for computer creatures

    @author   Jack Greenberg
    @date     Jan 25, 2020
    @version  1.0.0

    This file contains code from Griffiths & Griffiths "Head First C".
*/
#include <stdio.h>
#include <stdlib.h>

void prompt_user(char *card_name);
void update_count(int value, int *count);

/* Prompts the user for a card name.
Parameters:
    char *card_name: pointer to card_name variable that will hold the users input
*/
void prompt_user(char *card_name)
{
    puts("Enter the card_name: ");
    scanf("%2s", card_name);
}

/* update_count determines whether or not the count should be incremented or
    decremented and performs the correct operation.
Parameters:
    int val: The value to be checked
    int *count: The variable to be updated (incremented or decremented)
*/
void update_count(int val, int *count)
{
    if ((val > 2) && (val < 7)) {
        *count = *count + 1;
    } else if (val == 10) {
        *count = *count - 1;
    }
}

int main()
{
    char card_name[3];

    static int count = 0;
    while (card_name[0] != 'X') {
        prompt_user(card_name);

        int val = 0;
        
        switch(card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
            val = 10;
            break;
        case 'A':
            val = 11;
            break;
        case 'X':
            continue;
        default:
            val = atoi(card_name);
            if ((val < 1) || (val > 10)) {
                puts("I don't understand that value!");
                continue;
            }
        }

        update_count(val, &count);
        
        printf("Current count: %i\n", count);
    }
    return 0;
}

/*

`gcc -ansi -pedantic -Wall cards.c`

-ansi: Use the ANSI standard for C
-pedantic: Stricly use -ansi and reject any non-compliant code.
-Wall: Enable all compiler warnings

Using this command I got the warning:
```
cards.c: In function ‘main’:
cards.c:48:9: warning: ISO C90 forbids mixed declarations and code [-Wdeclaration-after-statement]
         int val = 0;
         ^~~
```

*/
