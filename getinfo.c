#include "s_shell.h"

/**
 * initialize_data - initializes data_t struct
 * @data: struct address
 */
void initialize_data(info_t *data)
{
	data->argument = NULL;
	data->arguments = NULL;
	data->path = NULL;
	data->argument_count = 0;
}

/**
 * populate_data - initializes data_t struct
 * @data: struct address
 * @args: argument vector
 */
void populate_data(info_t *data, char **args)
{
	int i = 0;

	data->filename = args[0];
	if (data->argument)
	{
		data->arguments = strtow(data->argument, " \t");
		if (!data->arguments)
		{

			data->arguments = malloc(sizeof(char *) * 2);
			if (data->arguments)
			{
				data->arguments[0] = _strdup(data->argument);
				data->arguments[1] = NULL;
			}
		}
		for (i = 0; data->arguments && data->arguments[i]; i++)
			;
		data->argument_count = i;

		replace_alias(data);
		replace_variables(data);
	}
}

/**
 * release_data - frees data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void release_data(info_t *data, int all)
{
	ffree(data->arguments);
	data->arguments = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->command_buffer)
			free(data->argument);
		if (data->environment)
			free_list(&(data->environment));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		ffree(data->environ);
		data->environ = NULL;
		bfree((void **)data->command_buffer);
		if (data->read_fd > 2)
			close(data->read_fd);
		cust_putchar(BUFFER_FLUSH);
	}
}
