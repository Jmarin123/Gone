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

int create_token(TokenList *list, TokenType token_type, const char *str) {
    // May need a check function to make sure we have space hehe.
    Token *token = &(list->tokens[list->current_index++]);
    token->type = token_type;

    size_t len = strlen(str);
    token->value = malloc(len + 1);
    if (!token->value) return 0;

    memcpy(token->value, str, len);
    token->value[len] = '\0';
    return 1;
}

TokenType keyword_lookup(const char *str){
    if(strcmp(str, "if") == 0) return TOKEN_IF;
    if(strcmp(str, "for") == 0) return TOKEN_FOR;
    if(strcmp(str, "int") == 0) return TOKEN_INT;
    if(strcmp(str, "bool") == 0) return TOKEN_BOOL;
    return TOKEN_VARIABLE;
}

// TokenType keynum_lookup() {

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
            int start = pointer;
            while (isalnum(buffer[pointer]) || buffer[pointer] == '_') pointer++;
            int len = pointer - start;
            // Max length of variables...Maybe make this bigger.
            if (len > 255) return 0;
            // Arbitrary but we need a bigger num i think..
            char temp[256];

            //Make a check here because the size of the length might be too big;
            memcpy(temp, &buffer[start], len);
            temp[len] = '\0';
            TokenType token = keyword_lookup(temp);

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