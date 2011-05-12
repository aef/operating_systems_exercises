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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/* global variable for child exit status */
int exit_status;

/*
 * Insertion point
 */

void sig_termination_handler(int signal, siginfo_t* daten, void* context);

int main(int argc, char** argv) {
    pid_t child;
    
    /* create sigaction struct */
    struct sigaction new_action;
    new_action.sa_handler = NULL; /* disabled normal handler */
    new_action.sa_sigaction = sig_termination_handler; /* handler callback with metadata */
    new_action.sa_flags =   SA_SIGINFO | /* use metadata handler instead of normal handler */
                            SA_NOCLDSTOP | /* only notify for termination not for stop or continue */
                            SA_NOCLDWAIT; /* terminate children directly  */
    new_action.sa_restorer = NULL; /* not used */

    sigemptyset(&new_action.sa_mask); /* create a empty signalset for ignore mask */

    /*
     * register sig_child_handler
     */
    if (sigaction(SIGCHLD, &new_action, NULL) == -1) {
        perror("sigaction not successful");
    }

    /*
     * create child
     */
    if ((child = fork()) == 0) {
        sleep(10);
        return 5;
    } else {
        wait(0);
    }

    return EXIT_SUCCESS;
}

/* 
 * SIGCHLD singnal handler
 * signal: received signal id (not used)
 * data: struct containing additional information about received signal
 * context: additional execution context information (not used)
 */
void sig_termination_handler(int signal, siginfo_t* data, void* context) {

    exit_status = data->si_status;
    printf("%i\n", data->si_status);

}