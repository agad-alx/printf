#include "main.h"

/**
 * get_argument_size - Determine the size to cast the argument for printf
 * @format: The formatted string containing format specifiers
 * @index: A pointer to the current index in the format string
 *
 * Return: The calculated argument size.
 */
int get_argument_size(const char *format, int *index)
{
	int current_index = *index + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = SIZE_LONG;
	else if (format[current_index] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*index = current_index - 1;
	else
		*index = current_index;

	return (size);
}
