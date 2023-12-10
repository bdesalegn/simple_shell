#include "s_shell.h"
/**
 * cust_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int cust_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * cust_strcmp - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zeroe 0
 */
int cust_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * cust_starts_with - checks if needle starts with haystack
 * @hay: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *cust_starts_with(const char *hay, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * cust_strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *cust_strcat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (result);
}
