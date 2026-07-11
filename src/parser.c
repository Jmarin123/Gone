#include "parser.h"

int ast(Parser *p) {
    Token *top_val = expect(p, TOKEN_DEC_VAR);
    if (top_val == NULL) {
        printf("RAAHH\n");
        return 0;
    }
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

Token *expect(Parser *p, TokenType type) {
    Token *t = consume(p);
    // TODO: add 
    if (t->type != type) {
        fprintf(stderr, "Expected ? got %s\n", type, t->value);
        return NULL;
    }
    return t;
}