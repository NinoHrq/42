/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:30 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:36:31 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	you_shall_not_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env || *path_env == '\0')
		setenv("PATH", "/bin:/usr/bin", 1);
}

int	calcul_check_path(char **check_path)
{
	int	i;

	i = 0;
	while (check_path[i])
	{
		if (ft_strcmp(check_path[i], "|") == 0)
			break ;
		i++;
	}
	i++;
	return (i);
}

void	check_path_in_or_with_pipe(char *input, t_ee *ee)
{
	char	**split_input;
	char	*path;

	split_input = ft_split(input, ' ');
	path = find_command_path(split_input[0]);
	if (path)
		ee->confirmed_command = 1;
	free_split(split_input);
	free(path);
	return ;
}

char	*save_initial_path(t_ee *ee)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (ee->envp[i])
	{
		if (ee->envp[i][0] == 'P' && ee->envp[i][1] == 'A'
			&& ee->envp[i][2] == 'T' && ee->envp[i][3] == 'H'
			&& ee->envp[i][4] == '=')
		{
			tmp = ft_strdup(ee->envp[i]);
			break ;
		}
		i++;
	}
	return (tmp);
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (ft_strlonglen(envp) + 1));
	i = 0;
	check_variable_oldpwd(envp);
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
