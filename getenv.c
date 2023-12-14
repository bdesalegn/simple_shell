#include "s_shell.h"

/**
 * obtain_environment - returns the string array copy of our environment
 * @details: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **obtain_environment(info_t *details)
{
	if (!details->environ || details->env_changed)
	{
		details->environ = cust_list_to_strings(details->env);
		details->env_changed = 0;
	}
	return (details->environ);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @details: Structure containing potential arguments. Used to maintain.
 * @property: the string environment variable property
 *  Return: 1 on delete, 0 otherwise
 */
int remove_environment_variable(info_t *details, char *property)
{
	list_t *node = details->env;
	size_t i = 0;
	char *p;

	if (!node || !property)
		return (0);

	while (node)
	{
		p = cust_starts_with(node->str, property);
		if (p && *p == '=')
		{
			details->env_changed = remove_node_at_index(&(details->env), i);
			i = 0;
			node = details->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (details->env_changed);
}

/**
 * update_environment_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @details: Structure containing potential arguments. Used to maintain
 * @property: the string environment variable property
 * @value: the string environment variable value
 *  Return: Always 0
 */
int update_environment_variable(info_t *details, char *property, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!property || !value)
		return (0);

	buf = malloc(cust_strlen(property) + cust_strlen(value) + 2);
	if (!buf)
		return (1);
	copyString(buf, property);
	cust_strcat(buf, "=");
	cust_strcat(buf, value);
	node = details->env;
	while (node)
	{
		p = cust_starts_with(node->str, property);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			details->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	append_node(&(details->env), buf, 0);
	free(buf);
	details->env_changed = 1;
	return (0);
}
