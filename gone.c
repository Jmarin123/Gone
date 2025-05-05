#include "gone.h"

int main(int argc, char** argv) {
    // Give proper message
    if (argc <= 1) { return EXIT_FAILURE; }

    int result = ends_with(argv[1], ".gone");
    if (result == 0) { return EXIT_FAILURE; }
    char *buffer = file_to_string(argv[1]);
    if (!buffer) { return EXIT_FAILURE; }

    Token *Tokens = lex(buffer);
    free(buffer);
    return EXIT_SUCCESS;
}