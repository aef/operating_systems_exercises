/*
 * Collaborative work of:
 *
 * Alexander E. Fischer
 * Axel Sorge
 * Daniel Meißner
 *
 * Created: 11.5.2011
 *
 * Used system functions: fork, wait, sleep, memset, time, localtime_r, strftime
 * For more information see the corresponding Man Pages.
 *
 * This program is an example for creating three children, waiting for there
 * termination. On child termination timestamp, run duration, and the PID of the
 * child should be displayed.
 *
 * No known limitations, implemented as described in exercise 3-1a.
 * Just compile and run from terminal.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define CHILD_COUNT 3

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    int children_terminated = 0;
    pid_t children[CHILD_COUNT];

    time_t fork_time;
    struct tm broken_time;
    time_t stop_time;

    char buffer[BUFSIZ];
    memset(buffer, 0, BUFSIZ);

    fork_time = time(NULL);

    if ((children[0] = fork()) == 0) {
        
        printf("First child: %i\n", getpid());
        sleep(5);
        
        stop_time = time(NULL);
        localtime_r(&stop_time, &broken_time);
        strftime(buffer, BUFSIZ, "%H:%M:%S", &broken_time);
        printf("current time: %s duration: %lis\n", buffer, (long) (stop_time - fork_time));

    } else if ((children[1] = fork()) == 0) {

        printf("Second child: %i\n", getpid());
        sleep(10);
        
        stop_time = time(NULL);
        localtime_r(&stop_time, &broken_time);
        strftime(buffer, BUFSIZ, "%H:%M:%S", &broken_time);
        printf("current time: %s duration: %lis\n", buffer,  (long) (stop_time - fork_time));
    } else if ((children[2] = fork()) == 0) {
        
        printf("Third child: %i \n", getpid());
        sleep(15);
        
        stop_time = time(NULL);
        localtime_r(&stop_time, &broken_time);
        strftime(buffer, BUFSIZ, "%H:%M:%S", &broken_time);
        printf("current time: %s duration: %lis\n", buffer, (long) (stop_time - fork_time));
    } else {

        int i;
        for (i = 0; i < CHILD_COUNT; i++) {

            if (children[i] == -1) {
                children_terminated++;
                perror("Parent: child fork failed");
            }
        }

        while (children_terminated < CHILD_COUNT) {
            printf("Parent: Child %i terminated\n", (int) wait(0));
            children_terminated++;
        }

        puts("Parent: all children dead");
    }

    return EXIT_SUCCESS;
}
