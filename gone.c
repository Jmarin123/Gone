#include "gone.h"

int main(int argc, char** argv) {
    // Give proper message
    if (argc <= 1) { return EXIT_FAILURE; }
    char* buffer = 0;

    int result = ends_with(argv[1], ".gone");
    if (result == 0) { return EXIT_FAILURE; }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);

    if (!buffer) {
        perror("malloc");
        fclose(f);
        return EXIT_FAILURE;
    }

    size_t read = fread(buffer, 1, length, f);
    buffer[read] = '\0';
    fclose(f);

    Token *Tokens = lex(buffer);
    free(buffer);
    return EXIT_SUCCESS;
}