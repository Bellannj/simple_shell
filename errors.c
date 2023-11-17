#include "shell.h"

char *_itoa(int num);
int num_len(int num);
int _error_creat(char **args, int err);


/**
 * num_len - Count the digit length of a number.
 * @num: number to be counted.
 *
 * Return: digit length.
 */
int num_len(int num)
{
	int len = 1;
	unsigned int num1;
	

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Convert an int to a str.
 * @num: integer.
 *
 * Return: converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: array of arguments.
 * @err: error value.
 *
 * Return: error value.
 */
int _error_creat(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_enva(args);
		break;
	case 1:
		error = error_0(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_1_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_3_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
