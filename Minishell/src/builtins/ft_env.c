#include "../../minishell.h"

void	ft_env(t_ee *ee)
{
	int	i;

	if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
	{
		if (ee->copy_pwd == NULL)
			ee->copy_pwd = getcwd(NULL, 0);
		if (ee->if_unset__pwd == 0)
			printf("🌱 PWD=%s\n", ee->copy_pwd);
		if (ee->if_unset__shlvl == 0)
			printf("🌱 SHLVL=1\n");
		printf("🌱 _=/usr/bin/env\n");
		if (ee->copy_oldpwd && ft_strcmp(ee->copy_oldpwd, ee->copy_pwd) != 0
			&& (ee->if_unset__oldpwd == 0))
			printf("🌱 OLDPWD=%s\n", ee->copy_oldpwd);
	}
	else
	{
		i = 0;
		while (ee->envp[i])
		{
			if (ee->copy_oldpwd && (ee->envp[i + 1] == NULL)
				&& (ee->if_unset__oldpwd == 0))
				printf("🌱 OLDPWD=%s\n", ee->copy_oldpwd);
			printf("🌱 %s\n", ee->envp[i]);
			i++;
		}
	}
}

void	check_variable_oldpwd(char **envp)
{
	int	i;
	int	j;
	int	yes;

	i = 0;
	yes = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if ((ft_strcmpchar(envp[i][j], 'O') == 0)
				&& (ft_strcmpchar(envp[i][j + 1], 'L') == 0)
				&& (ft_strcmpchar(envp[i][j + 2], 'D') == 0))
			{
				yes = 1;
				break ;
			}
			j++;
		}
		if (yes == 1)
			break ;
		i++;
	}
	if (envp[i])
	{
		while (envp[i])
		{
			envp[i] = envp[i + 1];
			i++;
		}
	}
}
