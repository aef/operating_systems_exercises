#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

void child_termination_handler(int signal, siginfo_t* metadata, void* context);
void print_time(const time_t* given_timestamp);

time_t start_time;

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    pid_t parent;
    pid_t first_child;
    pid_t second_child;
    pid_t third_child;
    struct sigaction new_action;
    int child_count = 3;
    
    /* Setup signal handler for child termination */
    new_action.sa_handler = NULL;
    new_action.sa_sigaction = child_termination_handler;
    new_action.sa_flags = SA_SIGINFO | SA_NOCLDSTOP;
    
    sigemptyset(&new_action.sa_mask);

    if (sigaction(SIGCHLD, &new_action, NULL) != 0) {
        perror("Error registering signal handler for SIGCHLD");
        return EXIT_FAILURE;
    }

    /* Find and report own process ID */
    parent = getpid();

    print_time(NULL);
    printf("Parent: PID is %i\n", parent);

    print_time(NULL);
    puts("Parent: Forking children");

    /* Flush output stream to prohibit buffered content to be copied into the child processes */
    fflush(stdout);

    start_time = time(NULL);

    /* Fork point */
    if ((first_child = fork()) == 0) {
        /* Code for the first child */
        first_child = getpid();

        print_time(NULL);
        printf("First child: PID is %i\n", first_child);

        sleep(5);
    } else if ((second_child = fork()) == 0) {
        /* Code for the second child */
        second_child = getpid();

        print_time(NULL);
        printf("Second child: PID is %i\n", second_child);

        sleep(10);
    } else if ((third_child = fork()) == 0) {
        /* Code for the third child */
        third_child = getpid();

        print_time(NULL);
        printf("Third child: PID is %i\n", third_child);

        sleep(15);
    } else {
        /* Code for the parent */

        /* Handle forking errors */
        if (first_child == -1) {
            child_count -= 1;
            perror("Error forking first child");
        }

        if (second_child == -1) {
            child_count -= 1;
            perror("Error forking second child");
        }

        if (third_child == -1) {
            child_count -= 1;
            perror("Error forking third child");
        }

        /* Wait for all children to be dead */
        while (child_count > 0) {
            wait(0);
            child_count -= 1;
        }

        print_time(NULL);
        puts("Parent: Children all dead");
    }

    return EXIT_SUCCESS;
}

/*
 * Signal handler function for SIGCHLD
 */
void child_termination_handler(int signal, siginfo_t* metadata, void* context) {
    time_t now = time(NULL);

    /* Calculate the duration for which the process ran */
    int run_duration = now - start_time;

    print_time(&now);

    /* Report signal retrieval and process duration */
    printf("SIGCHLD received from PID %i (Duration: %is)\n", metadata->si_pid, run_duration);


}

/*
 * Prints a timestamp to STDOUT. If NULL is given, a timestamp is created.
 */
void print_time(const time_t* given_timestamp) {
    time_t timestamp;
    struct tm broken_time;
    char* buffer = NULL;

    /* If no timestamp is given, generate one */
    if (given_timestamp == NULL) {
        timestamp = time(NULL);
    } else {
        timestamp = *given_timestamp;
    }

    /* Calculate the local broken-time from unix epoch timestamp */
    localtime_r(&timestamp, &broken_time);

    /* Format the broken-time for output */
    buffer = malloc(BUFSIZ);
    strftime(buffer, BUFSIZ, "%H:%M:%S", &broken_time);

    /* Report to STDOUT */
    printf("%s ", buffer);

    /* Clean up */
    free(buffer);
}