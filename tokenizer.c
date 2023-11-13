#include "shell.h"

/**
 * tokenize_arguments - tokenize the command line into individual arguments.
 * @command: user input.
 *
 * Return: a pointer to an array of strings
 */

char **tokenize_arguments(char *command)
{
	char **arguments = malloc(MAX_ARGUMENTS * sizeof(char *));
	int arg_index = 0;
	int arg_size = MAX_ARGUMENTS;
	char *token;
	char *rest = command;

	while ((token = strtok_r(rest, " ", &rest)) != NULL)
	{
		arguments[arg_index++] = token;

		if (arg_index >= arg_size)
		{
			arg_size += MAX_ARGUMENTS;
			arguments = realloc(arguments, arg_size * sizeof(char *));
		}
	}
	arguments[arg_index] = NULL;
	return (arguments);
}

/**
 * free_arguments - free the dynamically allocated memory for the arguments.
 * @arguments: args to be passed.
 *
 * RETURN: NULL.
*/

void free_arguments(char **arguments)
{
	int i = 0;

	if (arguments == NULL)
		return;

	while (arguments[i] != NULL)
	{
		free(arguments[i]);
		i++;
	}
	free(arguments);
}
