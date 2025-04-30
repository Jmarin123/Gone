#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int main(int argc, char** argv) {
    if (argc <= 1) { return EXIT_FAILURE; }
    char* buffer = 0;
    long length;
    // Todo, get some safety checks for the file extension

    FILE* f = fopen(argv[1], "r");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f,0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer){
        // Testing this stuff!
    }
    return 0;
}