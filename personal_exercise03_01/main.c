
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    char* original_string = argv[1];
    char* insert_string   = argv[2];
    char* result_string;
    char* write_position;
    
    int original_length;
    int insert_length;
    int result_length;
    int insert_position = atoi(argv[3]);

    /* Report error and exit unless the correct amount of arguments is given */
    if (argc != 4) {
        fprintf(stderr, "Usage: command ORIGINAL_STRING INSERT_STRING INSERT_POSITION\n");
        return EXIT_FAILURE;
    }

    /* Measure and report the original string */
    original_length = strlen(original_string);
    printf("Original string: %s (Length: %i)\n", original_string, original_length);

    /* Measure and report the insert string */
    insert_length = strlen(insert_string);
    printf("Insert string: %s (Length: %i)\n", insert_string, insert_length);

    /* Report the insert position */
    printf("Insert position: %i\n", insert_position);

    /* If position is outside original string, report error and exit */
    if (insert_position < 0 || insert_position > original_length) {
        fprintf(stderr, "Invalid position\n");
        return EXIT_FAILURE;
    }

    /* Calculate length and allocate result string */
    result_length = original_length + insert_length;
    result_string = malloc(result_length + 1);

    /*
     * Set write position pointer to the start of result string and write the
     * first part of the original string.
     */
    write_position = result_string;
    strncpy(write_position, original_string, insert_position);

    /*
     * Move write position forward by the length of the already written part
     * of original string. There, write the insert string.
     */
    write_position += insert_position;
    strcpy(write_position, insert_string);

    /*
     * Move write position forward by the length of the insert string. There,
     * write the remaining part of the original string.
     */
    write_position += insert_length;
    strcpy(write_position, original_string + insert_position);

    /* Print the result string and its length */
    printf("Result string: %s (Length: %i)\n", result_string, result_length);

    /* Deallocate the result string */
    free(result_string);

    return EXIT_SUCCESS;
}
