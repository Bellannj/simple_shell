#include "shell.h"

char **_getenva(const char *var);
void free_envaro(void);
char **copeyenv(void);

/**
 * copeyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 * otherwise - a double pointer to the new copy.
 */
char **copeyenv(void)
{
	char **new_environ;
	int index;
	size_t size;
	

	for (size = 0; environ[size]; size++);

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_envaro - Frees the the environment copy.
 */
void free_envaro(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenva - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenva(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
