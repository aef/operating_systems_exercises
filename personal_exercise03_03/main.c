#include <stdio.h>
#include <stdlib.h>

double factorial(int factor);

int main(int argc, char** argv) {
    int i;

    for (i = 0; i <= 50; i++) {
        printf("% 2i! = %.0f\n", i, factorial(i));
    }

    return EXIT_SUCCESS;
}

/*
 * Calculates the factorial of max recursively
 */
double factorial(int factor) {
    if (factor == 0) {
        return 1.0;
    } else {
        return factorial(factor - 1) * factor;
    }
}
