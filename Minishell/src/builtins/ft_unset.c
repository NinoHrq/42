#include "../../minishell.h"


char	*parse_env_name(char *s)
{
	int i;

	i = 0;
	while (s[i] != '=')
		i++;
	s[i] = '\0';
	return (s);
}

void	ft_unset(char *input, t_ee *ee)
{
	char **args;
	char **new_envp;
	int i, j, k;
	int skip;
	int len;

	args = ft_split(input, ' ');
	if (!args || !args[1])
	{
		free_split(args);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if ((!ee->envp || !ee->envp[0]) && ft_strcmp(args[i], "PATH") == 0)
		{
			unsetenv("PATH");
			ee->lock_path = 1;
		}
		i++;
	}
	new_envp = malloc(sizeof(char *) * (ft_strlonglen(ee->envp) + 1));
	if (!new_envp)
	{
		free_split(args);
		return ;
	}
	i = 0;
	k = 0;
	while (ee->envp && ee->envp[i])
	{
		skip = 0;
		j = 1;
		while (args[j])
		{
			len = ft_strlen(args[j]);
			if (ft_strncmp(ee->envp[i], args[j], len) == 0 && ee->envp[i][len] == '=')
			{
				if (ft_strcmp("PATH", args[j]) == 0)
				{
					unsetenv("PATH");
					ee->path_is_not_able = 1;
				}
				skip = 1;
				break ;
			}
			j++;
		}
		if (!skip)
		{
			new_envp[k] = ft_strdup(ee->envp[i]);
			k++;
		}
		i++;
	}
	new_envp[k] = NULL;

	free_split(ee->envp);
	ee->envp = new_envp;
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "PWD") == 0)
			ee->if_unset__pwd = 1;
		if (ft_strcmp(args[i], "OLDPWD") == 0)
			ee->if_unset__oldpwd = 1;
		if (ft_strcmp(args[i], "SHLVL") == 0)
			ee->if_unset__shlvl = 1;
		i++;
	}
	free_split(args);
}
