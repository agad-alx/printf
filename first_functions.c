#include "main.h"

/************************* PRINT CHARACTER *************************/

/**
 * print_character - Prints a character
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_character(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(args, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INTEGER *************************/
/**
 * print_integer - Print integer
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_integer(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int number = va_arg(args, long int);
	unsigned long int num;

	number = convert_size_number(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)number;

	if (number < 0)
	{
		num = (unsigned long int)((-1) * number);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number in binary
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int binary_digits[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(args, unsigned int);
	m = 2147483648; /* 2^31 */
	binary_digits[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		binary_digits[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += binary_digits[i];
		if (sum || i == 31)
		{
			char binary_char = '0' + binary_digits[i];

			write(1, &binary_char, 1);
			count++;
		}
	}
	return (count);
}
