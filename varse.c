#include "shell.h"

/**
 * is_chain_delimiter - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->commandBufferType = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->commandBufferType = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		info->commandBufferType = CMD_CHAIN;
	}
	else
		return (0);
	*position = j;
	return (1);
}

/**
 * checkDelimiter - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void checkDelimiter(info_t *info, char *buffer, size_t *position, size_t start, size_t length)
{
	size_t j = *position;

	if (info->commandBufferType == CMD_AND)
	{
		if (info->status)
		{
			buffer[start] = 0;
			j = length;
		}
	}
	if (info->commandBufferType == CMD_OR)
	{
		if (!info->status)
		{
			buffer[start] = 0;
			j = length;
		}
	}

	*position = j;
}

/**
 * replaceAlias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = cust_node_starts_with(info->alias, info->arguments[0], '=');
		if (!node)
			return (0);
		free(info->arguments[0]);
		ptr = _findCharacter(node->str, '=');
		if (!ptr)
			return (0);
		ptr = duplicateString(ptr + 1);
		if (!ptr)
			return (0);
		info->arguments[0] = ptr;
	}
	return (1);
}

/**
 * replaceVariables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->arguments[i]; i++)
	{
		if (info->arguments[i][0] != '$' || !info->arguments[i][1])
			continue;

		if (!cust_strcmp(info->arguments[i], "$?"))
		{
			replaceString(&(info->arguments[i]),
							duplicateString(convert_to_string(info->status, 10, 0)));
			continue;
		}
		if (!cust_strcmp(info->arguments[i], "$$"))
		{
			replaceString(&(info->arguments[i]),
						duplicateString(convert_to_string(getpid(), 10, 0)));
			continue;
		}
		node = cust_node_starts_with(info->environment, &info->arguments[i][1], '=');
		if (node)
		{
			replaceString(&(info->arguments[i]),
						duplicateString(_findCharacter(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->arguments[i], duplicateString(""));
	}
	return (0);
}

/**
 * replaceString - replaces string
 * @oldStr: address of old string
 * @newStr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **oldStr, char *newStr)
{
	free(*oldStr);
	*oldStr = newStr;
	return (1);
}
