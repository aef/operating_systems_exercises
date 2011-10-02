#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

void* notify_cycle(void* parameters);

struct notify_cycle_t {
    char* name;
    unsigned int sleep_time;
};

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    pthread_t first_thread;
    pthread_t second_thread;

    struct notify_cycle_t first_thread_config;
    struct notify_cycle_t second_thread_config;

    first_thread_config.name = "first thread";
    first_thread_config.sleep_time = 3;

    second_thread_config.name = "second thread";
    second_thread_config.sleep_time = 5;

    pthread_create(&first_thread, NULL, notify_cycle, (void*)&first_thread_config);
    pthread_create(&second_thread, NULL, notify_cycle, (void*)&second_thread_config);

    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);

    puts("");

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