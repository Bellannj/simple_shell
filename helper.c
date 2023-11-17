#include "shell.h"


char *get_pid(void);
void free_arg_1(char **args, char **front);
void var_rep(char **args, int *exe_ret);
char *get_env_value(char *beginning, int len);

/**
 * free_arg_1 - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands.
 * @front:pointer to the beginning of args.
 */
void free_arg_1(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Return: current process ID or NULL on failure.
 */

char *get_pid(void)
{
	ssize_t file;
	size_t i = 0;
	char *buffer;
	

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable.
 * @len: length of the environmental variable.
 *
 * Return: If the variable is not found - an empty string.
 *Otherwise - the value of the environmental variable.
 */
char *get_env_value(char *beginning, int len)
{
	char *replacement = NULL, *temp, *var;
	char **var_addr;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenva(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * var_rep - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 */

void var_rep(char **line, int *exe_ret)
{
	char *replacement = NULL, *old_line = NULL, *new_line;
	int j, k = 0, len;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
