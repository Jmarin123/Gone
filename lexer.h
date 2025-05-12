#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_SEMICOLON,
    TOKEN_DO,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_IF,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACK,
    TOKEN_LEFT_PARENTHESIS,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EQUAL,
    TOKEN_VARIABLE,
    TOKEN_BOOL,
    TOKEN_INT
} TokenType;

typedef struct Token {
    TokenType type;
    char *value;
} Token;

typedef struct TokenList {
    Token *tokens;
    size_t capacity;
    size_t current_index;
} TokenList;

int init_token_list(TokenList *list);
int create_token(TokenList *list, TokenType token_type, const char *str);
int lex(const char *buffer, TokenList *list);
int free_tokens(TokenList *list);
#endif