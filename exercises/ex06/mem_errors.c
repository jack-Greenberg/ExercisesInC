/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    int never_allocated;
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));
    int array1[100];
    int *array2 = malloc(100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    read_element(array1, -1);
    read_element(array1, 100);

    // but it does bounds-check dynamic arrays
    read_element(array2, -1); // This is invalid because -1 is out of range, so valgrind complains
    read_element(array2, 100); // This doesn't make sense because 99 is outside the bounds of the dynamically allocated list (0, 99)

    // and it catches use after free
    free(use_after_free); 
    *use_after_free = 17; // This is bad because we are trying to write to a freed variable

    // never_free is definitely lost
    *never_free = 17;

    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
    free_anything(&never_allocated); // never_allocated was, well, never allocated, so we are freeing something that was never allocated. never_allocated is on the stack, not the heap

    free(free_twice);
    free(free_twice); // You are trying to free the same variable twice...

    return 0;
}
