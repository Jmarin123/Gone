#include "parser.h"

int ast(Parser *p) {
    printf("%s\n", peak(p)->value);
    return 1;
}

Token *peak(Parser *p) {
    return &p->tokenlist->tokens[p->current];
}

Token *consume(Parser *p) {
    return &p->tokenlist->tokens[p->current++];
}