#include "s_shell.h"

/**
 * cust_list_length - determines length of linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t cust_list_length(const list_t *ptr)
{
	size_t count = 0;

	while (ptr)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

/**
 * cust_list_to_strings - returns an array of strings of the list->str
 * @head_ptr: pointer to first node
 *
 * Return: array of strings
 */
char **cust_list_to_strings(list_t *head_ptr)
{
	list_t *current_node = head_ptr;
	size_t length = cust_list_length(head_ptr), j;
	char **strings_array;
	char *str;

	if (!head_ptr || !length)
		return (NULL);

	strings_array = malloc(sizeof(char *) * (length + 1));
	if (!strings_array)
		return (NULL);

	for (length = 0; current_node; current_node = current_node->next, length++)
	{
		str = malloc(cust_strlen(current_node->str) + 1);
		if (!str)
		{
			for (j = 0; j < length; j++)
				free(strings_array[j]);
			free(strings_array);
			return (NULL);
		}

		str = copyString(str, current_node->str);
		strings_array[i] = str;
	}
	strings_array[length] = NULL;
	return (strings_array);
}

/**
 * cust_print_list - prints all elements of a list_t linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t cust_print_list(const list_t *ptr)
{
	size_t count = 0;

	while (ptr)
	{
		cust_puts(convert_to_string(ptr->num, 10, 0));
		cust_putchar(':');
		cust_putchar(' ');
		cust_puts(ptr->str ? ptr->str : "(nil)");
		cust_puts("\n");
		ptr = ptr->next;
		count++;
	}
	return (count);
}

/**
 * cust_node_starts_with - returns node whose string starts with prefix
 * @node_ptr: pointer to list head
 * @prefix_str: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *cust_node_starts_with(list_t *node_ptr, char *prefix_str,
		char next_char)
{
	char *match = NULL;

	while (node_ptr)
	{
		match = cust_starts_with(node_ptr->str, prefix_str);
		if (match && ((next_char == -1) || (*match == next_char)))
			return (node_ptr);
		node_ptr = node_ptr->next;
	}
	return (NULL);
}

/**
 * cust_get_node_index - gets the index of a node
 * @head_ptr: pointer to list head
 * @node_ptr: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t cust_get_node_index(list_t *head_ptr, list_t *node_ptr)
{
	size_t index = 0;

	while (head_ptr)
	{
		if (head_ptr == node_ptr)
			return (index);
		head_ptr = head_ptr->next;
		index++;
	}
	return (-1);
}
