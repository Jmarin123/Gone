#include "lexer.h"

void init_token_list(TokenList *list){
    // Add a set init variable from header, 128 seems arbitrary i guess.
    list->capacity = 128;
    list->current_index = 0;
    list->tokens = malloc(sizeof(Token) * list->capacity);
    if (!list->tokens) {
        perror("Malloc failed");
        // Todo: Needs a clean-up task to free the string buffer
        exit(1);
    }
}

void create_token(const char *type, const char *value) {
    
}

Token *lex(const char *buffer) {
    
}