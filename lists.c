#include "s_shell.h"

/**
 * prepend_node - adds a node to the start of the list
 * @head_ptr: address of pointer to head node
 * @str_val: str field of node
 * @num_val: node index used by history
 *
 * Return: size of list
 */
list_t *prepend_node(list_t **head_ptr, const char *str_val, int num_val)
{
	list_t *new_head;

	if (!head_ptr)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	cust_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num_val;
	if (str_val)
	{
		new_head->str = duplicateString(str_val);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_ptr;
	*head_ptr = new_head;
	return (new_head);
}

/**
 * append_node - adds a node to the end of the list
 * @head_ptr: address of pointer to head node
 * @str_val: str field of node
 * @num_val: node index used by history
 *
 * Return: size of list
 */
list_t *append_node(list_t **head_ptr, const char *str_val, int num_val)
{
	list_t *new_node, *node;

	if (!head_ptr)
		return (NULL);

	node = *head_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	cust_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num_val;
	if (str_val)
	{
		new_node->str = duplicateString(str_val);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head_ptr = new_node;
	return (new_node);
}

/**
 * print_list_strings - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_strings(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		cust_puts(h->str ? h->str : "(nil)");
		cust_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_node_at_index - deletes node at given index
 * @head_ptr: address of pointer to first node
 * @index_val: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **head_ptr, unsigned int index_val)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head_ptr || !*head_ptr)
		return (0);

	if (!index_val)
	{
		node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head_ptr;
	while (node)
	{
		if (i == index_val)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * clear_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void clear_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
