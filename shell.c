#include "shell.h"
/**
 * main - the shell main .c file
 * Return: nothing
 */
int main(void)
{
	char command[BUFFER_SIZE];

	while (1)
	{
		printf("simple_shell$ ");
		fflush(stdout);
		if (fgets(command, BUFFER_SIZE, stdin) == NULL)
		{
			print("\n");
			break;  /* Exit on EOF or error*/
		}
		command[strcspn(command, "\n")] = '\0';
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if
			(pid == 0)
			{
				char *args[] = {command, NULL};

				execve(command, args, environ);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		else
		{
			int status;

			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
