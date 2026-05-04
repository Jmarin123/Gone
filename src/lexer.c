#include "lexer.h"


// All this work might go to waste
// pain..

int init_token_list(TokenList *list) {
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
    // Like if we go over the capacity
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

TokenType keyword_lookup(const char *str) {
    if(strcmp(str, "if") == 0) return TOKEN_IF;
    if(strcmp(str, "else") == 0) return TOKEN_ELSE;
    if(strcmp(str, "for") == 0) return TOKEN_FOR;
    if(strcmp(str, "int") == 0) return TOKEN_INT;
    if(strcmp(str, "bool") == 0) return TOKEN_BOOL;
    if(strcmp(str, "true") == 0) return TOKEN_TRUE;
    if(strcmp(str, "false") == 0) return TOKEN_FALSE;
    if(strcmp(str, "exit") == 0) return TOKEN_EXIT;
    if(strcmp(str, "return") == 0) return TOKEN_RETURN;
    if(strcmp(str, "do") == 0) return TOKEN_DO;
    if(strcmp(str, "while") == 0) return TOKEN_WHILE;

    return TOKEN_STR_VAR;
}

int free_tokens(TokenList *list) {
    if (!list || !list->tokens) return 0;
    for(size_t i = 0; i < list->current_index; i++){
        free(list->tokens[i].value);
        list->tokens[i].value = NULL;
    }
    free(list->tokens);
    list->tokens = NULL;
    return 1;
}

int lex(const char *buffer, TokenList *list) {
    // Should check if token list has a value
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
            memcpy(temp, &buffer[start], len);
            temp[len] = '\0';
            TokenType token;
            if (decimal_flag == 0){
                token = TOKEN_INT_VAR;
            } else {
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
        int two_letter_token = 0;
        switch(buffer[pointer]) {
            case '+':
                if (buffer[pointer+1] == '+') {
                    token_type = TOKEN_INCREMENT_OP;
                    two_letter_token = 1;
                } else if (buffer[pointer+1] == '=') {
                    token_type = TOKEN_EQUAL_INCREMENT_OP;
                    two_letter_token = 1;
                } else {
                    token_type = TOKEN_PLUS;
                }
                break;
            case '-':
                if (buffer[pointer+1] == '-') {
                    token_type = TOKEN_DECREMENT_OP;
                    two_letter_token = 1;
                } else if (buffer[pointer+1] == '=') {
                    token_type = TOKEN_EQUAL_DECREMENT_OP;
                    two_letter_token = 1;
                } else {
                    token_type = TOKEN_MINUS;
                }
                break;
            case '=':
                if (buffer[pointer+1] == '=') {
                    token_type = TOKEN_EQUALITY_OP;
                    two_letter_token = 1;
                } else {
                    token_type = TOKEN_EQUAL;
                }
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
                // TODO: ADD STRING VALUE
                size_t start_point = pointer;
                pointer++;
                if (buffer[pointer] == '"') {
                    // pass
                }
                //int start = pointer;
                int valid_string = 0;
                // Idea: mark the first " and if it errors our then point to that time.
                while (buffer[pointer] != '\n' && buffer[pointer] != '\0') {
                    if (buffer[pointer] == '"') {
                        valid_string = 1;
                        break;
                    }
                    pointer++;
                }
                if (!valid_string) return 0;

                break;
            case '#':
                // Comments!
                while (buffer[pointer] != '\n' && buffer[pointer] != '\0') pointer++;
                skip = 1;
                break;
        }

        if (skip) continue;
        int check;
        if (two_letter_token) {
            char temp[3] = {buffer[pointer], buffer[pointer+1], '\0'};
            check = create_token(list, token_type, temp);
            pointer++;
        } else {
            char temp[2] = {buffer[pointer], '\0'};
            check = create_token(list, token_type, temp);
        }
        if (!check) return 0;
        pointer++;
    }

    return 1;
}
