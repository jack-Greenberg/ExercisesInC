/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
Creates an array of size SIZE (5), prints the address to the first element
of the array, and then sets every element in the array to 42. Then
returns the a pointer to the first element of the array.

! There is an issue because after foo() finishes executing, the memory allocated
! for `array` is freed, but we still have a pointer to that place in memory,
! which we won't be able to access.

*/
int *foo() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

/*
Creates an array of size SIZE (5), prints the address of the first element,
and then populates the array with the numbers 0..4. Returns nothing.
*/
void bar() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

/*

1. The program will print '42' five times. It creates a list `array`
and sets it equal to the output of foo(), which is an int[5] filled
with the value (int) 42.

2. Compiling the file generated a warning: `function returns address of local variable`.
This means that the function defines a local variable `int[5] array` and returns its pointer,
but when the function is finished executing, the program will "forget" the values stored
in the memory of the pointees.

3. Running it prints out two memory addresses (both `0x7ffcb90e9de0`), which are the addresses
of the `array` variables in foo() and bar(). Then there is a segmentation fault. This is because
the memory allocated for `array` in foo() is deallocated after foo is finished running, and 
all that remains is the pointer to what was the first element in `array`. When main() tries
to access the values stored in `array` from foo(), the values stored in there have already
been replaced by the values from bar().

4. Commenting out the printf statements doesn't change, except the program
no longer prints out the memory addresses of the local variables of foo() and
bar().

*/
