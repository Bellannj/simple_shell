#include "shell.h"

/**
 * print - custom printf function.
 * @format: format string
 * Return: void
 */

void print(const char *format, ...)
{
	const char *p;
	va_list args;

	va_start(args, format);

	for (p = format; *p != '\0'; ++p)
	{
		if (*p == '%')
		{
			++p;
			switch (*p)
			{
				case 'd':
					printf("%d", va_arg(args, int));
					break;
				case 'f':
					printf("%f", va_arg(args, double));
					break;
				case 's':
					printf("%s", va_arg(args, char *));
					break;
				default:
					putchar(*p);
					break;
			}
		}
		else
		{
			putchar(*p);
		}
	}
	va_end(args);
}
