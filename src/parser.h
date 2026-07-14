#ifndef PARSER_H
#define PARSER_H
    
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

Node *ast(Parser *p);

typedef struct Parser {
    TokenList *tokenlist;
    size_t current;
} Parser;

typedef enum {
    NODE_BINOP,
    NODE_IDENTIFIER, // Like variable name
    NODE_INT_LITERAL, // int, string, double, etc.
    NODE_DOUBLE_LITERAL, // int, string, double, etc.

} NodeType;

typedef struct Node {
    NodeType x;
    union {
        char *identifier;
        struct { struct Node *left, *right} binop;
        // need to add a bunch of others
    };
} Node;

Token *peak(Parser *p);

Token *consume(Parser *p);

Token *expect(Parser *p, TokenType type);

Node *statement(Parser *p);

#endif