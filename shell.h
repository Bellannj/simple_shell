#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

extern char **environ;

char* custom_getline();
void print(const char* format, ...);
void free_arguments(char** arguments);
char** tokenize_arguments(char* command);

#endif
