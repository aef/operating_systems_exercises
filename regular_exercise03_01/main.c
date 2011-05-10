/*
 * Copyright Alexander E. Fischer <aef@raxys.net>, 2011
 *
 * This file is part of Alexander E. Fischer's exercise solution collection
 * for the course "Betriebssysteme" of the Bachelor Computer Science study
 * program at Hochschule Bonn-Rhein-Sieg in summer semester 2011.
 *
 * This collection is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This collection is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this collection.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Version: 0.1.0, 2011-05-09 (http://semver.org/)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

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
    int child_count = 3;
    int children_terminated = 0;
    pid_t children[child_count];
    
    /* Find and report own process ID */
    parent = getpid();

    print_time(NULL);
    printf("Parent: PID is %i\n", parent);

    print_time(NULL);
    puts("Parent: Forking children");

    /* Flush output stream to prohibit buffered content to be copied into the child processes */
    fflush(stdout);

    /* Fork point */
    int i;
    for (i = 0; i < child_count; i++) {
        if ((children[i] = fork()) == 0) {
            /* Code for each child */
            time_t stop_time;
            time_t start_time = time(NULL);
            first_child = getpid();

            print_time(&start_time);
            printf("Child %i: Start (PID: %i)\n", i + 1, first_child);

            sleep(5);

            stop_time = time(NULL);
            print_time(&stop_time);
            printf("Child %i: Exit (PID: %i, Duration: %li)\n", i + 1, first_child, stop_time - start_time);
        } else if (children[i] == -1) {
            children_terminated++;
            perror("Error forking child");
        }
    }

    if (children[i] > 0) {
        while (children_terminated < child_count) {
            wait(0);
            children_terminated++;
        }

        print_time(NULL);
        puts("Parent: Children all dead");
    }
/*
    if ((first_child = fork()) == 0) {
        time_t stop_time;
        time_t start_time = time(NULL);
        first_child = getpid();

        print_time(&start_time);
        printf("First child: Start (PID: %i)\n", first_child);

        sleep(5);

        stop_time = time(NULL);
        print_time(&stop_time);
        printf("First child: Exit (PID: %i, Duration: %li)\n", first_child, stop_time - start_time);
    } else if ((second_child = fork()) == 0) {
        time_t stop_time;
        time_t start_time = time(NULL);
        second_child = getpid();

        print_time(&start_time);
        printf("Second child: Start (PID: %i)\n", second_child);

        sleep(10);

        stop_time = time(NULL);
        print_time(&stop_time);
        printf("Second child: Exit (PID: %i, Duration: %li)\n", second_child, stop_time - start_time);
    } else if ((third_child = fork()) == 0) {
        time_t stop_time;
        time_t start_time = time(NULL);
        third_child = getpid();

        print_time(&start_time);
        printf("Third child: Start (PID: %i)\n", third_child);

        sleep(15);

        stop_time = time(NULL);
        print_time(&stop_time);
        printf("Third child: Exit (PID: %i, Duration: %li)\n", third_child, stop_time - start_time);
    } else {
*/

/*
        /* Code for the parent

        /* Handle forking errors
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
*/
/*
    /* Wait for all children to be dead
        while (child_count > 0) {
            wait(0);
            child_count -= 1;
        }

        print_time(NULL);
        puts("Parent: Children all dead");
    }
*/
    return EXIT_SUCCESS;
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