#include "s_shell.h"

/**
 * buffer_input - buffers chained commands
 * @information: parameter struct
 * @buffer: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *information, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_ptr = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &length_ptr, stdin);
#else
		bytes_read = _getline_cust(information, buffer, &length_ptr);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			information->linecount_flag = 1;
			remove_comments(*buffer);
			append_to_history_list(information, *buffer, information->histcount++);
			{
				*length = bytes_read;
				information->cmd_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * obtain_input - gets a line minus the newline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t obtain_input(info_t *information)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t iterator_i, iterator_j, length;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(information->argument), *pointer;

	writeCharacter(BUFFER_FLUSH);
	bytes_read = buffer_input(information, &buffer, &length);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		iterator_j = iterator_i; /* init new iterator to current buffer position */
		pointer = buffer + iterator_i; /* get pointer for return */
		checkDelimiter(information, buffer, &iterator_j, iterator_i, length);
		while (iterator_j < length)
		{
			if (is_chain_delimiter(information, buffer, &iterator_j))
				break;
			iterator_j++;
		}
		iterator_i = iterator_j + 1; /* increment past nulled ';'' */
		if (iterator_i >= length) /* reached end of buffer? */
		{
			iterator_i = length = 0; /* reset position and length */
			information->cmd_buffer_type = CMD_NORMAL;
		}
		*buffer_ptr = pointer; /* pass back pointer to current command position */
		return (cust_strlen(pointer)); /* return length of current command */
	}
	*buffer_ptr = buffer;
	return (bytes_read); /* return length of buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @information: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: result
 */
ssize_t read_buffer(info_t *information, char *buffer, size_t *size)
{
	ssize_t result = 0;

	if (*size)
		return (0);
	result = read(information->read_fd, buffer, READ_BUFFER_SIZE);
	if (result >= 0)
		*size = result;
	return (result);
}

/**
 * _getline_cust - gets the next line of input from STDIN
 * @information: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline_cust(info_t *information, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t iterator_i, buffer_length;
	size_t k;
	ssize_t read_result = 0, s = 0;
	char *pointer = NULL, *new_pointer = NULL, *c;

	pointer = *ptr;
	if (pointer && length)
		s = *length;
	if (iterator_i == buffer_length)
		iterator_i = buffer_length = 0;
	read_result = read_buffer(information, buffer, &buffer_length);
	if (read_result == -1 || (read_result == 0 && buffer_length == 0))
		return (-1);

	c = _findCharacter(buffer + iterator_i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_pointer = cust_realloc(pointer, s, s ? s + k : k + 1);
	if (!new_pointer) /* MALLOC FAILURE! */
		return (pointer ? free(pointer), -1 : -1);
	if (s)
		cust_strcat(new_pointer, buffer + iterator_i, k - iterator_i);
	else
		_copyString(new_pointer, buffer + iterator_i, k - iterator_i + 1);
	s += k - iterator_i;
	iterator_i = k;
	pointer = new_pointer;
	if (length)
		*length = s;
	*ptr = pointer;
	return (s);
}

/**
 * interruptHandler - blocks ctrl-C
 * @signal_number: the signal number
 *
 * Return: void
 */
void interruptHandler(__attribute__((unused))int signal_number)
{
	printString("\n");
	printString("$ ");
	writeCharacter(BUFFER_FLUSH);
}
