/*
 * Author: Alexander E. Fischer
 * Created on 04 April 2011, 02:01
 */

#include <stdio.h>
#include <stdlib.h>

/*
 *
 */
int main(int argc, char** argv) {
    int a;
    int b;

    if (argc != 3) {
        fputs("Usage: command NUMBER_A NUMBER B\n", stderr);
        return EXIT_FAILURE;
    }

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    printf("a + b = %i\n", a + b);
    printf("a - b = %i\n", a - b);
    printf("a * b = %i\n", a * b);
    printf("a / b = %i\n", a / b);
    printf("a %% b = %i\n", a % b);
    printf("a > b = %i\n", a > b);
    printf("a <= b = %i\n", a <= b);
    printf("a != b = %i\n", a != b);

    return EXIT_SUCCESS;
}