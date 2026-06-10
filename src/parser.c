#include "parser.h"

int ast(TokenList *list) {
    printf("%lu", list->current_index);
    return 1;
}
