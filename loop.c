#include "shell.h"

/**
 * ysh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int ysh(info_xyz *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			outputString("$ ");
		eput_char(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			setInfoFromArguments(info, av);
			builtin_ret = require_builtin(info);
			if (builtin_ret == -1)
				findCommand(info);
		}
		else if (interactive(info))
			outputCharacter('\n');
		releaseInfo(info, 0);
	}
	writeInfoHistory(info);
	releaseInfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * require_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int require_builtin(info_xyz *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", program_exit},
		{"env", system_env},
		{"help", program_help},
		{"history", shel_history},
		{"setenv", program_setenv},
		{"unsetenv", system_unsetenv},
		{"cd", shel_cd},
		{"alias", shel_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (stringCompare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 *findCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(info_xyz *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!checkDelimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = look_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		copy_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && checkCommandExistence(info, info->argv[0]))
			copy_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			puts_error(info, "not found\n");
		}
	}
}

/**
 * copy_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void copy_cmd(info_xyz *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			releaseInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				puts_error(info, "Permission denied\n");
		}
	}
}

