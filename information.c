#include "shell.h"

/**
 * clear_info - initializes info_xyz struct
 * @info: struct address
 */
void clear_info(info_xyz *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfoFromArguments - initializes info_xyz struct
 * @info: struct address
 * @av: argument vector
 */
void setInfoFromArguments(info_xyz *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtoword(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = dup_strd(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * releaseInfo - frees info_xyz struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void releaseInfo(info_xyz *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeLinkedList(&(info->env));
		if (info->history)
			freeLinkedList(&(info->history));
		if (info->alias)
			freeLinkedList(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		freeMemory((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		outputCharacter(BUF_FLUSH);
	}
}

