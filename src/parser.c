#include "parser.h"

Node *ast(Parser *p) {
    return statement(p);
}

Node *statement(Parser *p) {
    switch(peak(p)->type) {
        // Something something look through a switch
    }
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
    // TODO: cool if we add line number like:
    // "Expected if got test on line 13"
    if (t->type != type) {
        fprintf(stderr, "Expected %s got %s\n", token_to_string(type), t->value);
        return NULL;
    }
    return t;
}