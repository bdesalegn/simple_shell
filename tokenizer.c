#include "s_shell.h"

/**
 * **splitString - splits a string into words. Repeat delimiters are ignored
 * @inputStr: the input string
 * @delimiter: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString(char *inputStr, char *delimiter)
{
	int idx_i, idx_j, idx_k, idx_m, numWords = 0;
	char **resultArray;

	if (inputStr == NULL || inputStr[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (idx_i = 0; inputStr[idx_i] != '\0'; idx_i++)
		if (!is_delimiter(inputStr[idx_i], delimiter) &&
			(is_delimiter(inputStr[idx_i + 1], delimiter) || !inputStr[idx_i + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	resultArray = malloc((1 + numWords) * sizeof(char *));
	if (!resultArray)
		return (NULL);
	for (idx_i = 0, idx_j = 0; idx_j < numWords; idx_j++)
	{
		while (is_delimiter(inputStr[idx_i], delimiter))
			idx_i++;
		idx_k = 0;
		while (!is_delimiter(inputStr[idx_i + idx_k], delimiter) && inputStr[idx_i
				+ idx_k])
			idx_k++;
		resultArray[idx_j] = malloc((idx_k + 1) * sizeof(char));
		if (!resultArray[idx_j])
		{
			for (idx_k = 0; idx_k < idx_j; idx_k++)
				free(resultArray[idx_k]);
			free(resultArray);
			return (NULL);
		}
		for (idx_m = 0; idx_m < idx_k; idx_m++)
			resultArray[idx_j][idx_m] = inputStr[idx_i++];
		resultArray[idx_j][idx_m] = 0;
	}
	resultArray[idx_j] = NULL;
	return (resultArray);
}

/**
 * **splitString2 - splits a string into words
 * @inputStr: the input string
 * @delimiter: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString2(char *inputStr, char delimiter)
{
	int idx_i, idx_j, idx_k, idx_m, numWords = 0;
	char **resultArray;

	if (inputStr == NULL || inputStr[0] == 0)
		return (NULL);
	for (idx_i = 0; inputStr[idx_i] != '\0'; idx_i++)
		if ((inputStr[idx_i] != delimiter && inputStr[idx_i + 1] ==
					delimiter) ||
			(inputStr[idx_i] != delimiter && !inputStr[idx_i + 1]) || inputStr[idx_i + 1] == delimiter)
			numWords++;
	if (numWords == 0)
		return (NULL);
	resultArray = malloc((1 + numWords) * sizeof(char *));
	if (!resultArray)
		return (NULL);
	for (idx_i = 0, idx_j = 0; idx_j < numWords; idx_j++)
	{
		while (inputStr[idx_i] == delimiter && inputStr[idx_i] != delimiter)
			idx_i++;
		idx_k = 0;
		while (inputStr[idx_i + idx_k] != delimiter && inputStr[idx_i + idx_k] && inputStr[idx_i + idx_k] != delimiter)
			idx_k++;
		resultArray[idx_j] = malloc((idx_k + 1) * sizeof(char));
		if (!resultArray[idx_j])
		{
			for (idx_k = 0; idx_k < idx_j; idx_k++)
				free(resultArray[idx_k]);
			free(resultArray);
			return (NULL);
		}
		for (idx_m = 0; idx_m < idx_k; idx_m++)
			resultArray[idx_j][idx_m] = inputStr[idx_i++];
		resultArray[idx_j][idx_m] = 0;
	}
	resultArray[idx_j] = NULL;
	return (resultArray);
}
