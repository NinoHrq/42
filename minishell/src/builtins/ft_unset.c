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
	int i, j;
	int len;

	/////////////////////////// split dans une autre fonction pour la norme //
	args = ft_split(input, ' ');
	if (args[1] == NULL)
	{
		free_split(args);
		return ;
	}
	new_envp = malloc(sizeof(char *) * (ft_strlonglen(ee->envp) + 1));
	if (!new_envp)
	{
		free_split(args);
		return ;
	}
	/////////////////////////////////////////////////////////////////////////
	len = ft_strlen(args[1]);
	i = 0;
	j = 0;
	while (ee->envp[i])
	{
		if (ft_strncmp(ee->envp[i], args[1], len) == 0
			&& ee->envp[i][len] == '=')
		{
			i++;
			continue ;
		}
		new_envp[j] = ft_strdup(ee->envp[i]);
		j++;
		i++;
	}
	new_envp[j] = NULL;
	free_split(ee->envp);
	ee->envp = new_envp;
	unsetenv(args[1]);
	//// CAS SPECIFIQUE ////
	if (ft_strcmp(args[1], "PWD") == 0)
		ee->if_unset__pwd = 1;
	if (ft_strcmp(args[1], "OLDPWD") == 0)
		ee->if_unset__oldpwd = 1;
	if (ft_strcmp(args[1], "SHLVL") == 0)
		ee->if_unset__shlvl = 1;
	////////////////////////
	free_split(args);
}
