/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void foo()
{
    int bar = 5;
    printf("Address of foo: %p\n", foo);
    printf("Address of bar: %p\n", &bar);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(35);
    void *q = malloc(17);
    char *s = "Hello, World";

    foo();

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("Address of p is %p\n", &p);
    printf ("p points to %p\n", p);
    printf ("q points to %p\n", q);
    printf ("s points to %p\n", s);

    return 0;
}

/* Memory Diagram

3.
    ```
    Address of main is 0x55b2653306fa
    Address of var1 is 0x55b265531014
    Address of var2 is 0x7fff2dd8d0c4
    p points to 0x55b266431260
    s points to 0x55b265330854
    ```
                                  Addresses
    +---------------------------+ ----------------
    |STACK                      |
    |    var2 [5]               | < 0x7fff2dd8d0c4
    |    p    [->0x55b266431260]|
    |    s    [->0x55b265330854]|
    |                           |
    |---------------------------+
    |HEAP                       |
    |                           |
    |      [   (128B)  ]        | < 0x55b266431260
    |                           |
    |---------------------------+
    |GLOBALS                    |
    |    var1 [ ]               | < 0x55b265531014
    |                           |
    |---------------------------+
    |CONSTANTS                  |
    |    "Hello world"          | < 0x55b265330854
    |                           |
    |---------------------------+
    |CODE                       |
    |    main()                 | < 0x55b2653306fa
    |                           |
    +---------------------------+

4. Adding a second call of malloc() adds memory with a higher
address
5. main() creates a variable var2 with address A. main() calls foo()
which creates a variable (int) bar and adds it to the stack with
address B, and B is lower than A.
6. Calling malloc() twice with
    void *p = malloc(5);
    void *q = malloc(17);
leads to two addresses separated by 0x20, which is 32 in decimal. Question: so calling
malloc(n) for n in [1, 32] allocates 32 bytes of memory?

*/
