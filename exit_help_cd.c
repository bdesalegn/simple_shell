#include "s_shell.h"
/**
 * exit_shell - functions exits from the shell
 * @info_struct: Struct data that containing potential arguments.To maintain
 *          constant function prototype.
 *  Return: Always exits with a given exit status
 */
int exit_shell(info_t *info_struct)
{
	int exit_check;

	if (info_struct->argv[1])
	{
		exit_check = _erratoi(info_struct->argv[1]);
		if (exit_check == -1)
		{
			info_struct->status = 2;
			print_error(info_struct, "Illegal number: ");
			_eputs(info_struct->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info_struct->err_num = _erratoi(info_struct->argv[1]);
		return (-2);
	}
	info_struct->err_num = -1;
	return (-2);
}
/**
 * change_directory - changes the current directory of the shell process
 * @info_struct: Struct data that containing potential arguments.To maintain
 *          constant function prototype.
 * Return: Always 0
 */
int change_directory(info_t *info_struct)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>get change wd failure mesage here<<\n");
	if (!info_struct->argv[1])
	{
		target_dir = _getenv(info_struct, "HOME=");
		if (!target_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((target_dir = _getenv(info_struct, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (_strcmp(info_struct->argv[1], "-") == 0)
	{
		if (!_getenv(info_struct, "OLD_PWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info_struct, "OLD_PWD=")), _putchar('\n');
		chdir_ret =
			chdir((target_dir = _getenv(info_struct, "OLD_PWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(info_struct->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info_struct, "Can't change directory to ");
		_eputs(info_struct->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info_struct, "OLD_PWD", _getenv(info_struct, "PWD="));
		_setenv(info_struct, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * display_help - displays help information
 * @info_struct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int display_help(info_t *info_struct)
{
	char **arg_array;

	arg_array = info_struct->argv;
	_puts("calling help works. Function not yet developed \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
