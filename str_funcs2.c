#include "shell.h"

char *_strchr(char *s, char c);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strspn(char *s, char *accept);


/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 * If c is not found - NULL.
 */
char *_strchr(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of  which
 * consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - Compares two strings.
 * @str1: first string to be compared.
 * @str2: second string to be compared.
 *
 * Return: Positive byte difference if str1 > str2
 * 0 if str1 = str2
 * Negative byte difference if str1 < str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @str1: Pointer to a string.
 * @str2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if str1 is shorter than str2.
 *         0 if str1 and str2 match.
 *         Greater than 0 if str1 is longer than str2.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
