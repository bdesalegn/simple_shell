#include "s_shell.h"

/**
 * initialize_data - initializes data_t struct
 * @data: struct address
 */
void initialize_data(info_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * populate_data - initializes data_t struct
 * @data: struct address
 * @args: argument vector
 */
void populate_data(info_t *data, char **args)
{
	int i = 0;

	data->fname = args[0];
	if (data->arg)
	{
		data->argv = splitString(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = duplicateString(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replaceAlias(data);
		replaceVariables(data);
	}
}

/**
 * release_data - frees data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void release_data(info_t *data, int all)
{
	cust_free(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		cust_free(data->environ);
		data->environ = NULL;
		bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		cust_putchar(BUFFER_FLUSH);
	}
}
