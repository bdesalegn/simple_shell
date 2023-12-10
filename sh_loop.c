#include "s_shell.h"

/**
 * my_shell - main shell loop
 * @shell_info: the parameter & return info struct
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int my_shell(info_t *shell_info, char **arguments)
{
	ssize_t read_status = 0;
	int builtin_result = 0;

	while (read_status != -1 && builtin_result != -2)
	{
		initialize_data(shell_info);
		if (is_interactive(shell_info))
			printString("$ ");
		cust_putchar(BUF_FLUSH);
		read_status = obtain_input(shell_info);
		if (read_status != -1)
		{
			populate_data(shell_info, arguments);
			builtin_result = find_shell_builtin(shell_info);
			if (builtin_result == -1)
				find_shell_command(shell_info);
		}
		else if (is_interactive(shell_info))
			writeCharacter('\n');
		release_data(shell_info, 0);
	}
	save_history(shell_info);
	release_data(shell_info, 1);
	if (!is_interactive(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_result == -2)
	{
		if (shell_info->err_num == -1)
			exit(shell_info->status);
		exit(shell_info->err_num);
	}
	return (builtin_result);
}

/**
 * find_shell_builtin - finds a builtin command in the shell
 * @shell_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_shell_builtin(info_t *shell_info)
{
	int i, shell_builtin_result = -1;
	builtin_table shell_builtintbl[] = {
		{"exit", exit_shell},
		{"env", print_environment},
		{"help", display_help},
		{"history", display_history},
		{"setenv", set_environment_variable},
		{"unsetenv", unset_environment_variable},
		{"cd", change_directory},
		{"alias", manage_alias},
		{NULL, NULL}
	};

	for (i = 0; shell_builtintbl[i].type; i++)
		if (cust_strcmp(shell_info->argv[0], shell_builtintbl[i].type) == 0)
		{
			shell_info->line_count++;
			shell_builtin_result = shell_builtintbl[i].func(shell_info);
			break;
		}
	return (shell_builtin_result);
}

/**
 * find_shell_command - finds a command in PATH for the shell
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void find_shell_command(info_t *shell_info)
{
	char *cmd_path = NULL;
	int i, count;

	shell_info->path = shell_info->argv[0];
	if (shell_info->linecount_flag == 1)
	{
		shell_info->line_count++;
		shell_info->linecount_flag = 0;
	}
	for (i = 0, count = 0; shell_info->arg[i]; i++)
		if (!is_delimiter(shell_info->arg[i], " \t\n"))
			count++;
	if (!count)
		return;

	cmd_path = search_in_path(shell_info, get_environment_variable(shell_info,
				"PATH="), shell_info->argv[0]);
	if (cmd_path)
	{
		shell_info->path = cmd_path;
		fork_shell_command(shell_info);
	}
	else
	{
		if ((is_interactive(shell_info) || get_environment_variable(shell_info,
						"PATH=") ||
			 shell_info->argv[0][0] == '/') && is_executable(shell_info,
				 shell_info->argv[0]))
			fork_shell_command(shell_info);
		else if (*(shell_info->arg) != '\n')
		{
			shell_info->status = 127;
			print_custom_error(shell_info, "not found\n");
		}
	}
}

/**
 * fork_shell_command - forks an exec thread to run command in the shell
 * @shell_info: the parameter & return info struct
 *
 * Return: void
 */
void fork_shell_command(info_t *shell_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shell_info->path, shell_info->argv, obtain_environment
					(shell_info)) == -1)
		{
			release_data(shell_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shell_info->status));
		if (WIFEXITED(shell_info->status))
		{
			shell_info->status = WEXITSTATUS(shell_info->status);
			if (shell_info->status == 126)
				print_custom_error(shell_info, "Permission denied\n");
		}
	}
}
