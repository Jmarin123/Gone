#include "unity.h"
#include "lexer.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

static TokenList global_tokens;

void setUp() {
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, init_token_list(&global_tokens), "setUp: init_token_list failed");
}

void tearDown() {
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, free_tokens(&global_tokens), "tearDown: free_token failed");
}

void init_token_list_test() {
    TEST_ASSERT_EQUAL_INT_MESSAGE(128, global_tokens.capacity, "init_token_list_test: token list capacity is not 128");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, global_tokens.current_index, "init_token_list_test: token list current index is not 0");
    return;
}

void keyword_lookup_test() {
    TokenType do_token = keyword_lookup("do");
    TokenType while_token = keyword_lookup("while");
    TokenType for_token = keyword_lookup("for");
    TokenType if_token = keyword_lookup("if");
    TokenType int_token = keyword_lookup("int");
    TokenType bool_token = keyword_lookup("bool");
    TokenType true_token = keyword_lookup("true");
    TokenType false_token = keyword_lookup("false");
    TokenType return_token = keyword_lookup("return");
    TokenType exit_token = keyword_lookup("exit");
    TEST_ASSERT_EQUAL(do_token, TOKEN_DO);
    TEST_ASSERT_EQUAL(while_token, TOKEN_WHILE);
    TEST_ASSERT_EQUAL(for_token, TOKEN_FOR);
    TEST_ASSERT_EQUAL(if_token, TOKEN_IF);
    TEST_ASSERT_EQUAL(int_token, TOKEN_INT);
    TEST_ASSERT_EQUAL(bool_token, TOKEN_BOOL);
    TEST_ASSERT_EQUAL(true_token, TOKEN_TRUE);
    TEST_ASSERT_EQUAL(false_token, TOKEN_FALSE);
    TEST_ASSERT_EQUAL(return_token, TOKEN_RETURN);
    TEST_ASSERT_EQUAL(exit_token, TOKEN_EXIT);
    return;
}

void create_token_test(){
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, create_token(&global_tokens, TOKEN_IF, "if"), "unable to create 'if' token");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, global_tokens.current_index, "create_token_test: current index did not increase after creating token");
    TEST_ASSERT_EQUAL_STRING("if", global_tokens.tokens[0].value);
    return;
}


// If we wanna access gone files use test/<File name>

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(init_token_list_test);
    RUN_TEST(keyword_lookup_test);
    RUN_TEST(create_token_test);
    UNITY_END();
    return 0;
}