#include "lexer.h"

int init_token_list(TokenList *list){
    // Add a set init variable from header, 128 seems arbitrary i guess.
    list->capacity = 128;
    list->current_index = 0;
    list->tokens = malloc(sizeof(Token) * list->capacity);
    if (!list->tokens) {
        perror("Malloc failed");
        return 0;
    }
    return 1;
}

// void create_token(const char *type, const char *value) {
    
// }

int lex(const char *buffer, TokenList *list) {
    int result = init_token_list(list);
    if (result == 0) {
        return 0;
    }
    size_t pointer = 0;
    while (buffer[pointer] != '\0') {
        if (isalpha(buffer[pointer])){
            // Start off as a variable or some sort of reserved character
            pointer++;
            continue;
        } else if (isdigit(buffer[pointer])) {
            // Just look at it as a value
            pointer++;
            continue;
        } else if (isblank(buffer[pointer])){
            pointer++;
            continue;   
        }
        pointer++;

    }
    return 1;
}