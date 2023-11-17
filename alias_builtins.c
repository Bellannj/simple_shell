#include "shell.h"

void print_alias(alias_t *alias);
void set_alias(char *var_name, char *value);
int shellby_alias(char **args, char __attribute__((__unused__)) **start);

/**
 * shellby_alias - either prints all aliases, specific
 * aliases, or sets an alias.
 * @args:array of argument.
 * @start: Double pointer to the beginning of arg.
 *
 * Return: on error occurs -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **start)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = _error_creat(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}

/**
 * set_alias -set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias.
 */
void set_alias(char *var_name, char *value)
{
	
	char *new_value;
	int leng, j, k;
	alias_t *temp = aliases;
	

	*value = '\0';
	value++;
	leng = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (leng + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int leng = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (leng + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, leng);
	free(alias_string);
}
/**
 * replace_aliases - eplace any matching alias
 * with their value.
 * @args:pointer to the arguments.
 *
 * Return: pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	char *new_value;
	int i;
	

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_arg_1(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
