#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TOKEN_SEMICOLON,
    // TOKEN_DO,
    // TOKEN_WHILE, Maybe set the Words value later?
    // TOKEN_FOR,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACK,
    TOKEN_LEFT_PARENTHESIS,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EQUAL,
} TokenType;

typedef struct Token {
    TokenType type;
    char *value;
    struct Token *next;
} Token;

typedef struct TokenList {
    Token *tokens;
    size_t capacity;
    size_t current_index;
} TokenList;

void init_token_list(TokenList *list);
void create_token(const char *type, const char *value);

Token *lex(const char *buffer);

#endif