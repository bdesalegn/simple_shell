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
		exit_check = str_to_int(info_struct->argv[1]);
		if (exit_check == -1)
		{
			info_struct->status = 2;
			print_custom_error(info_struct, "Illegal number: ");
			cust_puts(info_struct->argv[1]);
			cust_putchar('\n');
			return (1);
		}
		info_struct->err_num = str_to_int(info_struct->argv[1]);
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
		printString("TODO: >>get change wd failure mesage here<<\n");
	if (!info_struct->argv[1])
	{
		target_dir = get_environment_variable(info_struct, "HOME=");
		if (!target_dir)
			chdir_ret = chdir((target_dir = get_environment_variable
						(info_struct, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (cust_strcmp(info_struct->argv[1], "-") == 0)
	{
		if (get_environment_variable(info_struct, "OLD_PWD="))
		{
			printString(current_dir);
			writeCharacter('\n');
			return (1);
		}
		printString(get_environment_variable(info_struct, "OLD_PWD=")), writeCharacter('\n');
		chdir_ret = chdir((target_dir = get_environment_variable
					(info_struct, "OLD_PWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(info_struct->argv[1]);
	if (chdir_ret == -1)
	{
		print_custom_error(info_struct, "Can't change directory to ");
		cust_puts(info_struct->argv[1]), cust_putchar('\n');
	}
	else
	{
		update_environment_variable(info_struct, "OLD_PWD", get_environment_variable(info_struct, "PWD="));
		update_environment_variable(info_struct, "PWD", getcwd(buffer, 1024));
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
	printString("calling help works. Function not yet developed \n");
	if (0)
		printString(*arg_array);
	return (0);

