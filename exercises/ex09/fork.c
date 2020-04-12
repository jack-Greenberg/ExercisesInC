/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

int global_variable = 20;

char static_variable[] = "I'm static!";
// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    int *heap_variable = malloc(sizeof(int));
    *heap_variable = 1;

    int stack_variable = 10;

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            *heap_variable = *heap_variable + 1;
            stack_variable++;
            global_variable++;
            printf("CHILD: Heap variable after increment: %d\n", *heap_variable);
            printf("CHILD: Stack variable after increment: %d\n", stack_variable);
            printf("CHILD: Global variable after increment: %d\n", global_variable);
            printf("CHILD: Address of main(): %p\n", &main);
            printf("CHILD: Address of static variable: %p\n", &static_variable);
            child_code(i);
            exit(i);
        }
    }

    /* parent continues */
    *heap_variable = *heap_variable + 1;
    stack_variable++;
    global_variable++;
    printf("PARENT: Heap variable after increment: %d\n", *heap_variable);
    printf("PARENT: Stack variable after increment: %d\n", stack_variable);
    printf("PARENT: Global variable after increment: %d\n", global_variable);
    printf("PARENT: Address of main(): %p\n", &main);
    printf("PARENT: Address of static variable: %p\n", &static_variable);
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}


/*
 * The child processes don't share the same stack, global, or heap variables. I tried incrementing each variable and then printing it,
 * but each time the value was the same. Processes utilize "copy-on-write", which lets them use the same memory until the memory is
 * written to, and then the kernel copies the memory into a different space so that the processes have their own dedicated chunk
 * of memory
 *
 * The processes do share code and static segments, though. When we run the code, we can see that they use the same memory addresses.
 */
