#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdarg.h>

extern char **environ;


void print(const char* format, ...);

#endif
