#include "shell.h"

void _unsetenv(void);
void _history(void);
void _setenv(void);
void help_env_1(void);

/**
 * help_env_1 - Displays information on the shellby builtin command 'env'.
 */
void help_env_1(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * _setenv - Displays information on the shellby builtin command 'setenv'.
 */
void _setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * _unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void _unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
