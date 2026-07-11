#include "parser.h"

int ast(Parser *p) {
    return 1;
}

Token *peak(Parser *p) {
    if (p->current >= p->tokenlist->current_index) {
        return &p->tokenlist->tokens[p->tokenlist->current_index-1];
    }
    return &p->tokenlist->tokens[p->current];
}

Token *consume(Parser *p) {
    return &p->tokenlist->tokens[p->current++];
}