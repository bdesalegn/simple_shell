#include "s_shell.h"

/**
 * _copyString - copies a string
 * @destination: the destination string to be copied to
 * @source: source of teh string
 * @numChars: the number of characters to be copied
 * Return: the concatenated string
 */

char *_copyString(char *destination, char *source, int numChars)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < numChars - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < numChars)
	{
		j = i;
		while (j < numChars)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_concatenateStrings - concatenates two strings
 *@first_str: the first string
 *@second_str: the second string
 *@num_bytes: the number of bytes to be maximally used
 *Return: the concatenated string
 */
char *_concatenateStrings(char *first_str, char *second_str, int num_bytes)
{
	int i, j;
	char *s = first_str;

	i = 0;
	j = 0;
	while (first_str[i] != '\0')
	i++;
	while (second_str[j] != '\0' && j < num_bytes)
	{
		first_str[i] = second_str[j];
		i++;
		j++;
	}
	if (j < num_bytes)
		first_str[i] = '\0';
	return (s);
}

/**
 **_findCharacter - locates a character in a string
 *@string: the string to be parsed
 *@character: the character to look for
 *Return: (string) a pointer to the memory area of the string
 */
char *_findCharacter(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}
