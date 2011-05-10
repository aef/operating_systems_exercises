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
    char input_buffer[BUFSIZ];
    int a;
    int b;

    printf("Value for a: ");
    fgets(input_buffer, BUFSIZ, stdin);
    sscanf(input_buffer, "%i", &a);

    printf("Value for b: ");
    fgets(input_buffer, BUFSIZ, stdin);
    sscanf(input_buffer, "%i", &b);

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

