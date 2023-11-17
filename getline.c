#include "shell.h"

void lineptr_assign(char **lineptr, size_t *n, char *buffer, size_t b);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates a memory.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size of the allocated space for ptr.
 * @new_size: The size for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *If new_size == 0 and ptr is not NULL - NULL.
 *Otherwise - a pointer to the reallocated memory block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	
	char *ptr_copy, *filler;
	void *mem;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * lineptr_assign - Reassigns the line ptr for _getline.
 * @lineptr: buffer to store input string.
 * @n: size of lineptr.
 * @buffer: string to assign to lineptr.
 * @b: size of buffer.
 */
void lineptr_assign(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a stream.
 * @lineptr: buffer to store the input.
 * @n: size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t ret;
	static ssize_t input;
	int r;
	char c = 'x', *buffer;
	

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	lineptr_assign(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
