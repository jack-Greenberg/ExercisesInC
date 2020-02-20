/* tee.c - read from standard input and write to standard output and files.

Usage:
    tee [OPTIONS] [FILES...]

Description:
    Copy standard input to each FILE, and also to standard output.
        -a, --append
            append to the given FILEs, do not overwrite

Author:
    Jack Greenberg

Based on Linux command of the same name

Huge thank you to Manu Patil for his help debugging :)

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

char *FILE_MODE = "w";

int main(int argc, char *argv[])
{
    char buffer[255];
    char ch;
    int NUM_FILES; // Will store the number of files provided as arguments
    FILE **fd; // Will hold a list of file descriptors to write to
    int fd_count; // Will hold the number of things to write to (NUM_FILES + 1 (the +1 is for stdout))

	// Create long_options for long versions of the commandline flags
    static struct option const long_options[] =
    {
        {"append", no_argument, NULL, 'a'},
        {NULL, 0, NULL, 0}
    };

    while ((ch = getopt_long(argc, argv, "a", long_options, NULL)) != EOF) {
        switch(ch) {
            case 'a':
                FILE_MODE = "a";
                break;
            default:
                fprintf(stderr, "usage: tee [-a] [file ...]\n");
                exit(1);
        }
    }

    argc -= optind; // argc is now equal to the number of arguments after ./tee (no flags)
    argv += optind;

    fd[0] = stdout;
    fd_count = 1; // Number of things to write to

    NUM_FILES = argc; // Number of files is the same as argc

    int i; // i is an index for argv
    for (i = 0; i < NUM_FILES; i++, fd_count++) {
       fd[i + 1] = fopen(argv[i], FILE_MODE); // We use [i + 1] because when i = 0, we want to write to fd[1] since fd[0] is already taken by stdout

        if (fd[i + 1] == NULL) {
            fprintf(stderr, "Error opening a file: %s\n", argv[i]);
            exit(1);
        }
   }

    // Write to the various outputs
    while (fgets(buffer, sizeof buffer, stdin)) {
        for (int i = 0; i < fd_count; i++) {
            fputs(buffer, fd[i]);
        }
    }

    // Close all files that are open
    for (int k = NUM_FILES; k >= 1; k--) {
        fclose(fd[k]);
    }
}

/* SoftSys questions

3. It was very helpful to work along with the Mike Parker, Richard M. Stallman, and David MacKenzie solution from git.savannah.gnu.org because it provided some helpful hints and design choices that I took inspiration from, especially the concept of creating a list of file descriptors.

I was slowed down because I didn't keep good track of my variables. At one point, I had lots of for-loop indexes (i,j,k), as well as NUM_FILES, fd_count, and argc, and used a lot of them interchangably by adding or subtracting 1 to each of them depending on what was needed. After I figured out what I was doing wrong, I rewrote a lot of the functionality and created a list of variables that each had a specific meaning. From this I learned that it is a good idea to have variables with descriptive names that serve a single purpose.

At one point, I found it very helpful to step away from my computer and write down the basic structure of the program on a piece of paper and tackle each one separately and stitch it all together. 


4. In the professional code, there is a lot more error checking. There are descriptive messages for each possible error (reading stdin, opening files, writing files, etc.). There are also pieces of code that deal with interrupts (the -i argument). There is also code dealing with pipe issues, structs, and arrows (?) (->).

*/
