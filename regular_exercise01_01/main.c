/*
 * Collaborative work of:
 *
 * Alexander E. Fischer
 * Axel Sorge
 * Daniel Meißner
 *
 * Created: 11.5.2011
 *
 * Used system functions: sigaction, sigemptyset, fork, wait, sleep
 * For more information see the corresponding Man Pages.
 *
 * This program is an example for using a signal handler to receive the return
 * value from a terminated child process.
 *
 * No known limitations, implemented as described in exercise 3-3.
 * Just compile and run from terminal.
 *
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int glob = 6;
char buf[] = "a write to stdout\n";

int main(void) {
    int var;
    pid_t pid;

    var = 88;

    if (write(STDOUT_FILENO, buf, sizeof (buf) - 1) != sizeof (buf) - 1)
        perror("write error");

    printf("before fork\n");

    fflush(stdout);

    if ((pid = fork()) < 0)
        perror("fork error");
    else if (pid == 0) {
        glob++;
        var++;
    } else
        sleep(2);

    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}