#include "shell.h"

/**
 * custom_getline - read input from the user.
 *
 * Return: command.
 */
char *custom_getline(void)
{
	static char buffer[MAX_COMMAND_LENGTH];
	static int buffer_index;
	static int buffer_size;
	char *line = NULL;
	int line_index = 0;
	int line_size = 0;
	int c;

	while (1)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, sizeof(buffer));
			buffer_index = 0;

			if (buffer_size <= 0)
			{
				if (line_index > 0)
					break;
				return (NULL);
			}
		}
		c = buffer[buffer_index++];
		line = realloc(line, (line_size + 1) * sizeof(char));

		if (c == '\n')
		{
			line[line_index] = '\0';
			break;
		}
		else
		{
			line[line_index++] = c;
		}
	}
	return (line);
}

