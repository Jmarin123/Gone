#ifndef PARSER_H
#define PARSER_H
    
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int ast();

typedef struct Parser {
    TokenList *tokenlist;
    size_t current;
} Parser;


Token *peak(Parser *p);

Token *consume(Parser *p);

Token *expect(Parser *p, TokenType type);

#endif