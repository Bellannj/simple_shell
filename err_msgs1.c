#include "shell.h"

char *error_enva(char **args);
char *error_2_cd(char **args);
char *error_0(char **args);
char *error_3_syntax(char **args);
char *error_1_exit(char **args);

/**
 * error_enva - Creates an error message for shellby_env errors.
 * @args: array of arguments passed to the command.
 *
 * Return: error string.
 */
char *error_enva(char **args)
{
	int len;
	char *error, *list_str;
	

	list_str = _itoa(list);
	if (!list_str)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(list_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(list_str);
	return (error);
}

/**
 * error_0 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_0(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_1_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1_exit(char **args)
{
	int len;
	char *error, *list_str;
	

	list_str = _itoa(list);
	if (!list_str)
		return (NULL);

	len = _strlen(name) + _strlen(list_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(list_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return:error string.
 */
char *error_2_cd(char **args)
{
	char *error, *list_str;
	int len;

	list_str = _itoa(list);
	if (!list_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(list_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(list_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, list_str);
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(list_str);
	return (error);
}

/**
 * error_3_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_3_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(list);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
