#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/*
 * Insertion point
 */
int main(int argc, char** argv) {

    char* input_buffer = malloc(BUFSIZ);
    char* command_name = malloc(BUFSIZ);
    char* file_name = malloc(BUFSIZ);
    char operator;
    pid_t child;

    while (true) {
        printf("mysh2# ");

        fgets(input_buffer, BUFSIZ, stdin);
        sscanf(input_buffer, "%s %c %s", command_name, &operator, file_name);

        printf("Command: %s %c %s\n", command_name, operator, file_name);

        int descriptor_id2 = open(file_name, O_RDONLY);
        printf("descriptor: %i\n", descriptor_id2);

        fflush(stdout);

        if ((child = fork()) == 0) {
            int descriptor_id = 0;
            puts("Executing command...");
            printf("Opening file %s\n", file_name);

            switch (operator) {
                case '<':
                    descriptor_id = open(file_name, O_RDONLY);
                    close(0);
                    dup2(descriptor_id, 0);
                    break;
                case '>':
                    descriptor_id = open(file_name, O_WRONLY);
                    close(1);
                    dup2(descriptor_id, 1);
                    break;
            }

            if (descriptor_id == -1) {
                perror("Error opening file");
                return EXIT_FAILURE;
            }

            printf("File opened with descriptor id %d\n", descriptor_id);
            printf("Executing command %s\n", command_name);

            if (execlp(command_name, command_name, NULL) == -1) {
                perror("Executing command failed");

                free(input_buffer);
                free(command_name);
                free(file_name);

                return EXIT_FAILURE;
            }

        } else if (child == -1) {
            perror("Forking failed");
        } else {
            wait(0);
        }
        
    }
    
    free(input_buffer);
    free(command_name);
    free(file_name);

    return EXIT_SUCCESS;
}
