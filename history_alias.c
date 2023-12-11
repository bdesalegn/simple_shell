#include "s_shell.h"
/**
 * display_history - Print command history with line numbers.
 * @info: Structure with potential arguments (maintains constant prototype).
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	cust_print_list(info->history);
	return (0);
}
/**
 * remove_alias - Removes the alias identified by the provided string.
 * @info: Parameter struct
 * @str: The alias string
 * Return: 0 on success, 1 on error
 */

int remove_alias(info_t *info, char *str)
{
	char *equal_sign, equal_sign_char;
	int ret;

	equal_sign = _findCharacter(str, '=');
	if (!equal_sign)
		return (1);
	equal_sign_char = *equal_sign;
	*equal_sign = 0;
	ret = remove_node_at_index(&(info->alias), cust_get_node_index
			(info->alias, cust_node_starts_with(info->alias, str, -1)));
	*equal_sign = equal_sign_char;
	return (ret);
}
/**
 * add_alias - Adds an alias identified by the provided string.
 * @info:      Parameter struct
 * @str:       The string alias
 *
 * Return:    Always 0 on success, 1 on error
 */

int add_alias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _findCharacter(str, '=');
	if (!equal_sign)
		return (1);
	if (!*++equal_sign)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (append_node(&(info->alias), str, 0) == NULL);
}
/**
 * print_single_alias - Prints an alias string.
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_single_alias(list_t *node)
{
	char *equal_sign_position = NULL, *alias_start = NULL;

	if (node)
	{
		equal_sign_position = _findCharacter(node->str, '=');
		for (alias_start = node->str; alias_start <= equal_sign_position;
				alias_start++)
			writeCharacter(*alias_start);
		writeCharacter('\'');
		printString(equal_sign_position + 1);
		printString("'\n");
		return (0);
	}
	return (1);
}
/**
 * manage_alias - This function mimics the behavior of the alias built in.
 * @info: A pointer to a structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */

int manage_alias(info_t *info)
{
	int i = 0;
	char *equal_sign_position = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_single_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_position = _findCharacter(info->argv[i], '=');
		if (equal_sign_position)
			add_alias(info, info->argv[i]);
		else
			print_single_alias(cust_node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
