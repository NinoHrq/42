/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:51 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:36:52 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_env_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	s[i] = '\0';
	return (s);
}

void	remove_oldpwd_from_env(char **envp, int index)
{
	while (envp[index])
	{
		envp[index] = envp[index + 1];
		index++;
	}
}

int	find_oldpwd_index(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if ((ft_strcmpchar(envp[i][j], 'O') == 0)
				&& (ft_strcmpchar(envp[i][j + 1], 'L') == 0)
				&& (ft_strcmpchar(envp[i][j + 2], 'D') == 0))
			{
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

void	check_variable_oldpwd(char **envp)
{
	int	index;

	index = find_oldpwd_index(envp);
	if (index != -1)
		remove_oldpwd_from_env(envp, index);
}

char	*save_initial_home(t_ee *ee)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (ee->envp[i])
	{
		if (ee->envp[i][0] == 'H' && ee->envp[i][1] == 'O'
			&& ee->envp[i][2] == 'M' && ee->envp[i][3] == 'E'
			&& ee->envp[i][4] == '=')
		{
			tmp = ft_strdup(ee->envp[i]);
			break ;
		}
		i++;
	}
	return (tmp);
}

/*void	check_variable_oldpwd(char **envp)
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
}*/
