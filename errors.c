#include "s_shell.h"

/**
 * str_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int str_to_int(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_custom_error - prints an error message
 * @data: the parameter & return info struct
 * @error_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_custom_error(info_t *data, char *error_str)
{
	cust_puts(data->fname);
	cust_puts(": ");
	print_decimal(data->line_count, STDERR_FILENO);
	cust_puts(": ");
	cust_puts(data->argv[0]);
	cust_puts(": ");
	cust_puts(error_str);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*put_char)(char) =  cust_putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		put_char = putchar;
	if (input < 0)
	{
		absolute = -input;
		put_char('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			put_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	put_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *charset;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	charset = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = charset[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_first_comment - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_first_comment(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
