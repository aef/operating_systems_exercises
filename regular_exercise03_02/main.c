/*
 * Collaborative work of:
 *
 * Alexander E. Fischer
 * Axel Sorge
 * Daniel Meißner
 *
 * Created: 11.5.2011
 *
 * Used system functions: fork, sleep
 * For more information see the corresponding Man Pages.
 *
 * This program is an example for creating a child process and put it into
 * zombie state.
 *
 * No known limitations, implemented as described in exercise 3-2.
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
    pid_t child;


    if ((child = fork()) == 0) {
        printf("Message");

        printf("Child terminated");
    } else {
        printf("%i\n", (int) child);
        sleep(90);
    }

    return EXIT_SUCCESS;
}