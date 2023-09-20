#include "main.h"

/**
 * get_active_flags - Calculate active flags from the format string
 * @format: Formatted string containing format specifiers
 * @current_index: A pointer to the current index in the format string
 *
 * Return: Calculated flags
 */
int get_active_flags(const char *format, int *current_index)
{
	/* Flag characters: - + 0 # ' ' */
	/* Corresponding values: 1 2 4 8 16 */
	int i, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *current_index + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (i = 0; FLAGS_CH[i] != '\0'; i++)
		{
			if (format[curr_i] == FLAGS_CH[i])
			{
				flags |= FLAGS_ARR[i];
				break;
			}
		}

		if (FLAGS_CH[i] == 0)
			break;
	}

	*current_index = curr_i - 1;

	return (flags);
}
