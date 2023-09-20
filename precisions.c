#include "main.h"

/**
 * get_precision - Calculate the precision for printing
 * @format: The formatted string containing format specifiers
 * @index: A pointer to the current index in the format string
 * @args: List of arguments to be printed
 *
 * Return: The calculated precision value.
 */
int get_precision(const char *format, int *index, va_list args)
{
	int current_index = *index + 1;
	int precision = -1;

	if (format[current_index] != '.')
		return (precision);

	precision = 0;

	for (current_index += 1; format[current_index] != '\0'; current_index++)
	{
		if (is_digit(format[current_index]))
		{
			precision *= 10;
			precision += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_index++;
			precision = va_arg(args, int);
			break;
		}
		else
		{
			break;
		}
	}

	*index = current_index - 1;

	return (precision);
}
