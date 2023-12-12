#include "shell.h"

/**
 * program_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int program_exit(info_xyz *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = con_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			puts_error(info, "Illegal number: ");
			sys_eputs(info->argv[1]);
			eput_char('\n');
			return (1);
		}
		info->err_num = con_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * shel_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int shel_cd(info_xyz *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		outputString("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (stringCompare(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			outputString(s);
			outputCharacter('\n');
			return (1);
		}
		outputString(_getenv(info, "OLDPWD=")), outputCharacter('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		puts_error(info, "can't cd to ");
		sys_eputs(info->argv[1]), eput_char('\n');
	}
	else
	{
		updateEnvironment(info, "OLDPWD", _getenv(info, "PWD="));
		updateEnvironment(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * program_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int program_help(info_xyz *info)
{
	char **arg_array;

	arg_array = info->argv;
	outputString("help call works. Function not yet implemented \n");
	if (0)
		outputString(*arg_array); /* temp att_unused workaround */
	return (0);
}

