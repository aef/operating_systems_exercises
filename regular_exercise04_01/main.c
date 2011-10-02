#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* char_print(void* parameters);

struct repeated_character_t {
    char character;
    unsigned int repetitions;
};

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    pthread_t y_thread;
    pthread_t x_thread;

    struct repeated_character_t y_repetition;
    struct repeated_character_t x_repetition;

    y_repetition.character = 'y';
    y_repetition.repetitions = 5;

    x_repetition.character = 'x';
    x_repetition.repetitions = 7;

    pthread_create(&y_thread, NULL, char_print, (void*)&y_repetition);
    pthread_create(&x_thread, NULL, char_print, (void*)&x_repetition);

    pthread_join(y_thread, NULL);
    pthread_join(x_thread, NULL);

    puts("");

    return EXIT_SUCCESS;
}

void* char_print(void* parameters) {
    int i;
    struct repeated_character_t* repeated_character = (struct repeated_character_t*)parameters;
    
    for (i = 0; i < repeated_character->repetitions; i++) {
        putchar(repeated_character->character);
    }

    return NULL;
}