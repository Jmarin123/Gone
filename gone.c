#include "gone.h"

int main(int argc, char** argv) {
    // Give proper message
    if (argc <= 1) { return EXIT_FAILURE; }

    int result = ends_with(argv[1], ".gone");
    if (result == 0) { return EXIT_FAILURE; }
    char *buffer = file_to_string(argv[1]);
    if (!buffer) { return EXIT_FAILURE; }

    // Maybe add a better name than tokens lol
    TokenList tokens;
    if (!lex(buffer, &tokens)){
        free(buffer);
        return EXIT_FAILURE;
    }
    free(buffer);
    free(tokens.tokens);
    //Todo: ast = parser(&tokens)
    //Todo: Maybe mips interpreted? Maybe byte code.
    //Todo: Free tokens value
    return EXIT_SUCCESS;
}