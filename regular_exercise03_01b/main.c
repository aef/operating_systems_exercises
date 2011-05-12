/*
 * Collaborative work of:
 *
 * Alexander E. Fischer
 * Axel Sorge
 * Daniel Meißner
 *
 * Created: 11.5.2011
 *
 * Used system functions: fork
 * For more information see the corresponding Man Pages.
 *
 * This program is an example for creating and counting as much children as possible.
 *
 * No known limitations, implemented as described in exercise 3-1b.
 * Just compile and run from terminal.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    int child_count = 0;
    
    while (true) {
        if (fork() == 0) {
            break;
        }
        
        child_count++;
    }
    printf("Child count: %i\n", child_count);

    while (true);

    return EXIT_SUCCESS;
}