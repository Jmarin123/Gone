#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    // Reserved words
    TOKEN_DO,       // "Do"
    TOKEN_WHILE,    // "While"
    TOKEN_FOR,      // "For"
    TOKEN_IF,       // "If"
    TOKEN_ELSE,     // "Else"
    TOKEN_INT,      // "int"
    TOKEN_BOOL,     // "bool"
    TOKEN_TRUE,     // "true"
    TOKEN_FALSE,     // "false"

    // Reserved characters
    TOKEN_SEMICOLON,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACK,
    TOKEN_LEFT_PARENTHESIS,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EQUAL,
    TOKEN_INCREMENT_OP, // ++
    TOKEN_DECREMENT_OP, // ++
    TOKEN_EQUAL_INCREMENT_OP, // +=
    TOKEN_EQUAL_DECREMENT_OP, // -=
    TOKEN_EQUALITY_OP, // ==

    // Type Variable Reserve
    TOKEN_STR_VAR,
    TOKEN_INT_VAR,
    TOKEN_DEC_VAR,
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