#include "shell.h"
int (*get_builtin(char *command))(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int _shellby_help(char **args, char __attribute__((__unused__)) **front);
int shellby_exit(char **args, char **front);


/**
 * get_builtin - Matches a command with a corresponding
 * builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "help", _shellby_help },
		{ "setenv", shellby_setenv },
		{ "unsetenv", _shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "alias", shellby_alias },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shellby_exit - Causes normal process termination
 * for the shellby shell.
 * @args: Array of arguments containing the exit value.
 * @front:Double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 * If the given exit value is invalid - 2.
 * otherwise - exits with the given status value.
 *
 * Description: after returning -3, the program exits back in the main function.
 */
int shellby_exit(char **args, char **front)
{
	
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);
	int i, len_of_int = 10;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (_error_creat(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (_error_creat(--args, 2));

	args -= 1;
	free_envaro();
	free_arg_1(args, front);
	alias_list(aliases);
	exit(num);
}

/**
 * shellby_cd - Change the directory of the shellby process.
 * @args: array of arguments.
 * @front: double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char *oldpwd = NULL, *pwd = NULL;
	char **dir_info, *new_line = "\n";
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);

	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenva("OLDPWD") != NULL)
					(chdir(*_getenva("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (_error_creat(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (_error_creat(args, 2));
			}
		}
	}
	else
	{
		if (_getenva("HOME") != NULL)
			chdir(*(_getenva("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * _shellby_help - Displays info about shellby builtin commands.
 * @args: array of arguments.
 * @front:pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help1();
	else if (_strcmp(args[0], "alias") == 0)
		_alias_1();
	else if (_strcmp(args[0], "cd") == 0)
		_cd_1();
	else if (_strcmp(args[0], "exit") == 0)
		_exit_1();
	else if (_strcmp(args[0], "env") == 0)
		help_env_1();
	else if (_strcmp(args[0], "setenv") == 0)
		_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_2();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
