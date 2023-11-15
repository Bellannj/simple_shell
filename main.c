#include "shell.h"

/**
 * handle_exit_command - handles the logic for the "exit" command.
 * @arguments: argument.
 *
 * Return: 0 on success -1 on fail.
 */

void handle_exit_command(char **arguments)
{
	if (arguments[1] != NULL)
	{
		int status = atoi(arguments[1]);

		exit(status);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

/**
 * handle_env_command - handles the logic for the env command.
 *
 * Return: NULL.
 */

void handle_env_command(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		print("%s\n", *env);
		env++;
	}
}

/**
 * handle_other_command - handles logic for commands
 * other than "exit" and "env".
 * @arguments: arguments
 *
 * Return: void.
 */

void handle_other_command(char **arguments)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (strcmp(arguments[0], "/bin/ls") == 0)
		{
			execv(arguments[0], arguments);
			perror("execv");
			exit(EXIT_FAILURE);
		}
		else
		{
			search_and_execute_command(arguments);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
 * search_and_execute_command - attempts to locate the command by.
 * concatenating each directory path.
 * @arguments:args
 * Return: NULL
 */

void search_and_execute_command(char **arguments)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char *command_path = malloc(strlen(token) + strlen(arguments[0]) + 2);

		sprintf(command_path, "%s/%s", token, arguments[0]);

		if (access(command_path, F_OK) == 0)
		{
			arguments[0] = command_path;
			execv(arguments[0], arguments);
			perror("execv");
			exit(EXIT_FAILURE);
		}
		free(command_path);
		token = strtok(NULL, ":");
	}
	fprintf(stderr, "Command not found: %s\n", arguments[0]);
	exit(EXIT_FAILURE);
}

/**
 * main - entery point program.
 *
 * Return: 0 (EXIT_SUCCESS) -1 om (EXIT_FAILURE).
 */

int main(void)
{
	char *command;
	char **arguments;

	while (1)
	{
		print("simple_shell$ ");
		fflush(stdout);

		command = custom_getline();
		arguments = tokenize_arguments(command);

		if (command == NULL)
		{
			print("\n");
			break;
		}
		if (strcmp(arguments[0], "exit") == 0)
		{
			handle_exit_command(arguments);
		}
		else if (strcmp(arguments[0], "env") == 0)
		{
			handle_env_command();
		}
		else
		{
			handle_other_command(arguments);
		}
		free(arguments);
		free(command);
	}
	return (0);
}
