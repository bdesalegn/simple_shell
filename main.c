#include "s_shell.h"

/**
 * main - Entry point of the program
 * @ac: Argument count
 * @av: an array of strings representing the command-line arguments
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				cust_puts(av[0]);
				cust_puts(": 0: Can't open ");
				cust_puts(av[1]);
				cust_putchar('\n');
				cust_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	load_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
