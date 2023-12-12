#include "shell.h"

/**
 * system_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int system_env(info_xyz *info)
{
	printStringListElements(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_xyz *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * program_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int program_setenv(info_xyz *info)
{
	if (info->argc != 3)
	{
		sys_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (updateEnvironment(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * system_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int system_unsetenv(info_xyz *info)
{
	int i;

	if (info->argc == 1)
	{
		sys_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnvironmentVariable(info, info->argv[i]);

	return (0);
}

/**
 * initializeEnvList - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initializeEnvList(info_xyz *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		appendNode(&node, environ[i], 0);
	info->env = node;
	return (0);
}

