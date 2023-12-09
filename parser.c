#include "s_shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info_data: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info_data, char *file_path)
{
	struct stat st;

	(void)info_data;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_chars - duplicates characters
 * @source_str: the PATH string
 * @start_index: starting index
 * @end_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *copy_chars(char *source_str, int start_index, int end_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < end_index; i++)
		if (source_str[i] != ':')
			buffer[k++] = source_str[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * search_in_path - finds this command in the PATH string
 * @info_data: the info struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *search_in_path(info_t *info_data, char *path_string, char *command)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((cust_strlen(command) > 2) && cust_starts_with(command, "./"))
	{
		if (is_executable(info_data, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = copy_chars(path_string, current_pos, i);
			if (!*path)
				cust_strcat(path, command);
			else
			{
				cust_strcat(path, "/");
				cust_strcat(path, command);
			}
			if (is_executable(info_data, path))
				return (path);
			if (!path_string[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
