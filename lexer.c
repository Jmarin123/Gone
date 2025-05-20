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
    // Like if we go ove the capacity
    Token *token = &(list->tokens[list->current_index++]);
    token->type = token_type;

    size_t len = strlen(str);
    token->value = malloc(len + 1);
    if (!token->value) {
        perror("Malloc failed");
        return 0;
    }
    memcpy(token->value, str, len);
    token->value[len] = '\0';
    return 1;
}

TokenType keyword_lookup(const char *str){
    if(strcmp(str, "if") == 0) return TOKEN_IF;
    if(strcmp(str, "else") == 0) return TOKEN_ELSE;
    if(strcmp(str, "for") == 0) return TOKEN_FOR;
    if(strcmp(str, "int") == 0) return TOKEN_INT;
    if(strcmp(str, "bool") == 0) return TOKEN_BOOL;
    if(strcmp(str, "true") == 0) return TOKEN_TRUE;
    if(strcmp(str, "false") == 0) return TOKEN_FALSE;

    return TOKEN_STR_VAR;
}

int free_tokens(TokenList *list){
    for(size_t i = 0; i < list->current_index; i++){
        free(list->tokens[i].value);
    }
    free(list->tokens);
    return 1;
}

int lex(const char *buffer, TokenList *list) {
    if (init_token_list(list) == 0) {
        return 0;
    }
    int line_no = 1;
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
            int check = create_token(list, token, temp);
            if (!check) return 0;
            continue;
        } else if (isdigit(buffer[pointer])) {
            // Just look at it as a value

            int start = pointer;
            int decimal_flag = 0;
            while (isdigit(buffer[pointer]) || buffer[pointer] == '.') {
                if (buffer[pointer] == '.'){
                    if (decimal_flag == 1) return 0;
                    decimal_flag = 1;
                }
                pointer++;
            }
            int len = pointer - start;
            if (len > 25) return 0;
            // Temp size may be wrong
            char temp[25];

            //Make a check here because the size of the length might be too big;
            memcpy(temp, &buffer[start], len);
            temp[len] = '\0';
            TokenType token;
            if (decimal_flag == 0){
                token = TOKEN_INT_VAR;
            } else{
                token = TOKEN_DEC_VAR;
            }
            int check = create_token(list, token, temp);
            if (!check) return 0;
            continue;
        } else if (isblank(buffer[pointer]) || isspace(buffer[pointer])){
            if(buffer[pointer] == '\n') line_no++;
            pointer++;
            continue;
        }
        TokenType token_type;
        int skip = 0;
        switch(buffer[pointer]) {
            //NEED ++ because MANE
            case '+':
                token_type = TOKEN_PLUS;
                break;
            case '=':
                token_type = TOKEN_EQUAL;
                break;
            case ';':
                token_type = TOKEN_SEMICOLON;
                break;
            case '{':
                token_type = TOKEN_LEFT_BRACKET;
                break;
            case '}':
                token_type = TOKEN_RIGHT_BRACK;
                break;
            case '(':
                token_type = TOKEN_LEFT_PARENTHESIS;
                break;
            case ')':
                token_type = TOKEN_RIGHT_PARENTHESIS;
                break;
            case '"':
                // need to make a special case here because what if we have "variable"
                // Maybe let multiline strings exist?
                pointer++;
                if (buffer[pointer] == '"') {
                    // Empty string uhh I go
                }
                int start = pointer;
                int valid_string = 0;
                // Idea: mark the first " and if ti errors our then point to that time.
                while (buffer[pointer] != '\n' && buffer[pointer] != '\0') {
                    if (buffer[pointer] == '"') {
                        valid_string = 1;
                        break;
                    }
                }
                if (!valid_string) return 0;

                break;
            case '#':
                // Comments!
                while (buffer[pointer] != '\n' && buffer[pointer] != '\0') pointer++;
                skip = 1;
                break;
        }
 
        if(skip) continue;
        char temp[2] = {buffer[pointer], '\0'};
        int check = create_token(list, token_type, temp);
        if (!check) return 0;
        pointer++;

    }

    return 1;
}