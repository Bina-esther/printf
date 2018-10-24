#include "holberton.h"

/**
 * print_c - Prints a character.
 * @list: A va_list pointing to the character to print.
 * @buffer: A character buffer to store the character in.
 *
 * Return: Always 1.
 */
int print_c(va_list list, char *buffer)
{
	unsigned char ch;

	ch = va_arg(list, int);
	if (ch == '\0')
		return (1);

	*buffer = ch;
	return (1);
}
