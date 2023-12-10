#include "s_shell.h"
/**
 * string_to_integer - function converts a string to an integer
 * @str: the string to be converted
 * Return: Always 0 if no numbers in string, converted number otherwise
 */
int string_to_integer(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
/**
 * is_interactive - returns true if simple shell is in interactive mode
 * @infoData: struct address
 *
 * Return: Always 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *infoData)
{
	return (isatty(STDIN_FILENO) && infoData->readfd <= 2);
}

/**
 * is_delimiter - checks if the character is a delimiter or note
 * @character: the char value to check
 * @delimiter: the delimiter string variable
 * Return: Return 1 if true, 0 if false
 */
int is_delimiter(char character, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}
/**
 *checkAlpha - checks for alphabetical character
 *@character: The character variable to input
 *Return: Always 1 if character is alphabetic, 0 else
 */

int checkAlpha(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' &&
				character <= 'Z'))
		return (1);
	else
		return (0);
}
