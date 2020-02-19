#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *FILE_MODE = "w";

int main(int argc, char *argv[])
{
    char buffer[255];
    char ch;
    FILE *out;

    // argv += 1; // First argv is the command called (./tee)

    while ((ch = getopt(argc, argv, "a")) != EOF) {
        switch(ch) {
            case 'a':
                FILE_MODE = "a";
                break;
            case '?':
                fprintf(stderr, "Unrecognized option: '-%c'\n", optopt);
            default:
                exit(1);
                break;
        }
    }

    while (fscanf(stdin, "%s", buffer) != EOF) {
        for (int i = 1; i < argc; i++) {
            if (!(out = fopen(argv[i], FILE_MODE))) {
                fprintf(stderr, "Can't open file: '%s'\n", argv[i]);
            }
            fprintf(out, "%s", buffer);
        }
    }
}
