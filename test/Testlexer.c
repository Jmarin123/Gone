#include "unity.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

void setUp() {

}

void tearDown() {

}

void simple_lexer() {
    return;
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(simple_lexer);
    UNITY_END();
    // FILE *fptr;
    // fptr = fopen("simple_int_assignment.gone", "r");
    // if (fptr == NULL) {
    //     printf("Error: Unable to open the file.\n");
    //     exit(1);
    // }
    // char data[100];
    // while (fgets(data, 100, fptr) != NULL) {
    //     printf("%s", data);
    // }

    // fclose(fptr);
    return 0;
}