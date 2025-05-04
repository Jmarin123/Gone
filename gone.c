#include "gone.h"

int main(int argc, char** argv) {
    // Give proper message
    if (argc <= 1) { return EXIT_FAILURE; }
    char* buffer = 0;
    long length;

    int result = EndsWith(argv[1], ".gone");
    if (result == 0) { return EXIT_FAILURE; }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
        fread(buffer, 1, length, f);
    }
    fclose(f);

    if (buffer){
        printf("%ld\n", strlen(buffer));
    }
    return EXIT_SUCCESS;
}