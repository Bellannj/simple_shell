#include "shell.h"

void print(const char *str)
{
    ssize_t bytes_written = write(STDOUT_FILENO, str, strlen(str));
    if (bytes_written == -1)
    {
        const char *error_msg = strerror(errno);
        write(STDERR_FILENO, error_msg, strlen(error_msg));
    }
}