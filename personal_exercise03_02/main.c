#include <stdio.h>
#include <stdlib.h>

double factorial(int max);

int main(int argc, char** argv) {
    int i;

    for (i = 0; i <= 50; i++) {
        printf("% 2i! = %.0f\n", i, factorial(i));
    }

    return EXIT_SUCCESS;
}

/*
 * Calculates the factorial of max iteratively
 */
double factorial(int max) {
    double result = 1.0;
    int i;

    for (i = 1; i <= max; i++) {
        result *= i;
    }

    return result;
}
