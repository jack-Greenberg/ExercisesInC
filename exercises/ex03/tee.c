#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *FILE_MODE = "w";

int main(int argc, char *argv[])
{
    char buffer[255] = {};
    char ch;
    FILE *out;

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

    argc -= optind;
    argv += optind;

    size_t num_bytes_read;
    while ((num_bytes_read = read(STDIN_FILENO, buffer, sizeof buffer)) > 0) {

        for (int i = 0; i < argc; i++) {

            if (!(out = fopen(argv[i], FILE_MODE))) {
                fprintf(stderr, "Can't open file: '%s'\n", argv[i]);
                exit(1);
            }

            fwrite(buffer, num_bytes_read, 1, out);
            fclose(out);
        }

        // Write to stdout
        fwrite(buffer, num_bytes_read, 1, stdout);
    }
}
