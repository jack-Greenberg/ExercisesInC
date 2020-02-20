/* tee.c - read from standard input and write to standard output and files.

Usage:
    tee [OPTIONS] [FILES...]

Description:
    Copy standard input to each FILE, and also to standard output.
        -a
            append to the given FILEs, do not overwrite

Author:
    Jack Greenberg

Based on Linux command of the same name

Huge thank you to Manu Patil for his help debugging :)

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *FILE_MODE = "w";

int main(int argc, char *argv[])
{
    char buffer[255];
    char ch;
    int NUM_FILES; // Will store the number of files provided as arguments
    FILE **fd; // Will hold a list of file descriptors to write to
    int fd_count; // Will hold the number of things to write to (NUM_FILES + 1 (the +1 is for stdout))

    while ((ch = getopt(argc, argv, "a")) != EOF) {
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
