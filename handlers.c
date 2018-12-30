/*
 * File: handlers.c
 * Auth: Brennan D Baraban
 *       Michael Klein
 */

#include "holberton.h"

/**
 * handle_flags - Matches a flag with its corresponding value.
 * @flag: A pointer to the potential flag.
 *
 * Return: If a flag character is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_flags(const char *flag)
{
	int i, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_length(const char *modifier)
{
	if (*modifier == 'h')
		return (SHORT);
	else if (*modifier == 'l')
		return (LONG);
	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int handle_width(va_list args, const char *modifier)
{
	int value;

	if ((*modifier <= '0' || *modifier > '9') && (*modifier != '*'))
		return (0);

	if (*modifier == '*')
	{
		value = va_arg(args, int);
		if (value < 0)
			return (0);
		return (value);
	}

	return (*modifier - '0');
}

/**
 * handle_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 *
 * Return: If a precision modifier is matched - its vaue.
 *         Otherwise - 0.
 */
int handle_precision(va_list args, const char *modifier)
{
	int value;

	if (*modifier != '.')
		return (0);

	if ((*(modifier + 1) <= '0' || *(modifier + 1) > '9') &&
	     *(modifier + 1) != '*')
		return (0);

	if (*(modifier + 1) == '*')
	{
		value = va_arg(args, int);
		if (value < 0)
			return (0);
		return (value);
	}

	return (*(modifier + 1) - '0');
}

/**
 * handle_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @specifier: A pointer to a potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,\
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', convert_r},
		{'R', convert_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
