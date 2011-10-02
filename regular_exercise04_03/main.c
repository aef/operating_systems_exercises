#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void* notify_cycle(void* parameters);

struct notify_cycle_t {
    char* name;
    unsigned int sleep_time;
};

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    pthread_t thread;

    struct notify_cycle_t thread_config;

    thread_config.name = "Alert";
    thread_config.sleep_time = 5;

    pthread_create(&thread, NULL, notify_cycle, (void*)&thread_config);

    if (getchar()) {
        pthread_kill(thread, SIGTERM);
    }

    return EXIT_SUCCESS;
}

void* notify_cycle(void* parameters) {
    struct notify_cycle_t* config = (struct notify_cycle_t*)parameters;
    
    while (true) {
        printf("%s\n", config->name);
        sleep(config->sleep_time);
    }

    return NULL;
}