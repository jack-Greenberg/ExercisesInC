/* adder.c - Arithmetic and adding for adept amateurs
Adder accepts input of up to 15 integers and returns their sum.

@author Jack Greenberg
@date   02-04-2020

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARRAY_SIZE      15 // Max number of inputs

/*
vet_input() takes an input buffer and a pointer to a flag and
ensures that the buffer contains only `ints`. If so, the function
finishes executing and allows main() to continue. If there are alpha
characters, the function prints a warning and sets a flag to continue
the main while loop
*/
void vet_input(char buffer[32], int* flag) 
{
    int j = 0;
    while (buffer[j] != '\0') {
        if (!isdigit(buffer[j]) && (buffer[j] != '\n')) {
            *flag = 1;
            puts("Input not recognized; use a valid number");
            j++;
            break;
        } else if (buffer[j] == '\n') {
            break;
        } else {
	    j++;
	}
    }
}

/*
add() takes an int[15] called `array` and the number of elements in the array
and prints the sum of the elements in `array`.
*/
void add(int array[ARRAY_SIZE], int size)
{
    int i;
    int sum = 0;

    for (i = 0; i < size; i++) {
        sum += array[i];
    }
    printf("Sum: %d\n", sum);
}

int main()
{
    int array[ARRAY_SIZE];
    char buffer[32];
    int i = 0;

    while (fgets(buffer, sizeof buffer + 1, stdin) != NULL) {

        if (i == ARRAY_SIZE) {
            printf("Max input length reached, continuing...\n");
            break;
        }

        int CONTINUE_FLAG = 0;

        vet_input(buffer, &CONTINUE_FLAG);

        /*
        If the continue flag is set to 1, the loop will continue
        and the flag will get reset at the top of the loop.
        This exists to vet the input and ensure the buffer only
        includes ints.
        */
        if (CONTINUE_FLAG == 1) {
            continue;
        }

        /*
        This chunk only executes if there are no issues with the
        input buffer.
        */
        array[i] = atoi(buffer);
        i++;
    }

    add(array, i); // Pass i to add() to let add() know how many numbers to sum

    return 0;
}
