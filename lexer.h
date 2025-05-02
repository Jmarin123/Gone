#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_EOF
} TokenType;

typedef struct Token {
    TokenType type;
    char *value;
    struct Token *next;
} Token;

Token *create_token(const char *type, const char *value);

#endif