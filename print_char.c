#include "s_shell.h"
/**
 * cust_puts - Prints an input string.
 * @str_input: The string to be printed.
 *
 * Return: Nothing.
 */
void cust_puts(char *str_input)
{
	int index = 0;

	if (!str_input)
		return;
	while (str_input[index] != '\0')
	{
		cust_putchar(str_input[index]);
		index++;
	}
}

/**
 * cust_putchar - Writes the character 'char_input' to stderr
 * @char_input: The character to be printed
 *
 * Return: On success, returns 1. On error, returns -1.
 */
int cust_putchar(char char_input)
{
	static int count;
	static char buffer[WRITE_BUF_SIZE];

	if (char_input == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(2, buffer, count);
		count = 0;
	}
	if (char_input != BUF_FLUSH)
		buffer[count++] = char_input;
	return (1);
}

/**
 * put_to_fd - Writes the character c to the specified file descriptor.
 * @char_input: The character to be written.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: On success, returns 1. On error, returns -1.
 */
int put_to_fd(char char_input, int file_descriptor)
{
	static int count;
	static char buffer[WRITE_BUF_SIZE];

	if (char_input == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buffer, count);
		count = 0;
	}
	if (char_input != BUF_FLUSH)
		buffer[count++] = char_input;
	return (1);
}

/**
 * cust_puts_to_fd - This function writes the contents of str_input to
 *                  the specified file descriptor.
 * @str_input: The string to be printed.
 * @file_descriptor: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */

int cust_puts_to_fd(char *str_input, int file_descriptor)
{
	int index = 0;

	if (!str_input)
		return (0);
	while (*str_input)
	{
		index += put_to_fd(*str_input++, file_descriptor);
	}
	return (index);
}
