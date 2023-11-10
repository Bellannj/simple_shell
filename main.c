#include "shell.h"

int main() {
    char buffer[BUFFER_SIZE];
    pid_t child_pid;

    int is_interactive = isatty(STDIN_FILENO);

    while (1) {
        if (is_interactive) {
            printf("($) ");
            fflush(stdout);
        }

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
            break;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        child_pid = fork();

        if (child_pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Split the command and its arguments
            char *args[BUFFER_SIZE];
            int arg_count = 0;
            char *token = strtok(buffer, " ");
            while (token != NULL) {
                args[arg_count++] = token;
                token = strtok(NULL, " ");
            }
            args[arg_count] = NULL;

            if (execvp(args[0], args) == -1) {
                perror("execvp error");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}
