#include "s_shell.h"

/**
 * fetch_history_file - gets the history file
 * @information: parameter struct
 *
 * Return: allocated string containing history file
 */

char *fetch_history_file(info_t *information)
{
	char *buffer, *directory;

	directory = get_environment_variable(information, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (cust_strlen(directory) +
				cust_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	copyString(buffer, directory);
	cust_strcat(buffer, "/");
	cust_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * save_history - creates a file, or appends to an existing file
 * @information: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int save_history(info_t *information)
{
	ssize_t file_descriptor;
	char *file_name = fetch_history_file(information);
	list_t *node = NULL;

	if (!file_name)
		return (-1);
	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		cust_puts_to_fd(node->str, file_descriptor);
		put_to_fd('\n', file_descriptor);
		}
		put_to_fd(BUF_FLUSH, file_descriptor);
		close(file_descriptor);
		return (1);
}

/**
 * load_history - reads history from file
 * @information: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int load_history(info_t *information)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *file_name = fetch_history_file(information);

	if (!file_name)
		return (0);
	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stats))
		file_size = file_stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			append_to_history_list(information, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		append_to_history_list(information, buffer + last, line_count++);
	free(buffer);
	information->histcount = line_count;
	while (information->histcount-- >= HIST_MAX)
		remove_node_at_index(&(information->history), 0);
	renumber_history_list(information);
	return (information->histcount);
}

/**
 * append_to_history_list - adds entry to a history linked list
 * @information: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history line count, histcount
 *
 * Return: Always 0
 */
int append_to_history_list(info_t *information, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	append_node(&node, buffer, line_count);
	if (!information->history)
		information->history = node;
	return (0);
}

/**
 * renumber_history_list - renumbers the history linked list after changes
 * @information: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history_list(info_t *information)
{
	list_t *node = information->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (information->histcount = i);
}
