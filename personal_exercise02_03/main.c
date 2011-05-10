/*
 * Author: Alexander E. Fischer
 * Created on 04 April 2011, 02:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool string_equal(char* first_string, char* second_string);

int main(int argc, char** argv) {
    int a;
    int b;
    char* operation = NULL;

    if (argc < 3) {
        fputs("Usage: command NUMBER_A NUMBER_B OPERATION\n", stderr);
        return EXIT_FAILURE;
    } else if (argc == 4) {
        operation = argv[3];
    } else if (argc > 4) {
        fprintf(stderr, "Ignoring unnecessary arguments (count: %i)\n", argc - 4);
    }

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    if (operation == NULL || string_equal(operation, "+")) {
        printf("%i + %i = %i\n", a, b, a + b);
    }

    if (operation == NULL || string_equal(operation, "-")) {
        printf("%i - %i = %i\n", a, b, a - b);
    }

    if (operation == NULL || string_equal(operation, "*")) {
        printf("%i * %i = %i\n", a, b, a * b);
    }

    if (operation == NULL || string_equal(operation, "/")) {
        printf("%i / %i = %i\n", a, b, a / b);
    }

    if (operation == NULL || string_equal(operation, "%")) {
        printf("%i %% %i = %i\n", a, b, a % b);
    }

    if (operation == NULL || string_equal(operation, ">")) {
        printf("%i > %i = %i\n", a, b, a > b);
    }
    
    if (operation == NULL || string_equal(operation, "<=")) {
        printf("%i <= %i = %i\n", a, b, a <= b);
    }

    if (operation == NULL || string_equal(operation, "!=")) {
        printf("%i != %i = %i\n", a, b, a != b);
    }

    return EXIT_SUCCESS;
}

bool string_equal(char* first_string, char* second_string) {
    return strcmp(first_string, second_string) == 0;
}