#include "unity.h"
#include "lexer.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

void setUp() {

}

void tearDown() {

}

void init_token_list_test() {
    TokenList tokens;
    int res = init_token_list(&tokens);
    TEST_ASSERT(res == 1);
    TEST_ASSERT_EQUAL_INT(tokens.capacity, 128);
    TEST_ASSERT_EQUAL_INT(tokens.current_index, 0);
    free_tokens(&tokens);
    return;
}

// If we wanna access gone files use test/<File name>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(init_token_list_test);
    UNITY_END();
    return 0;
}