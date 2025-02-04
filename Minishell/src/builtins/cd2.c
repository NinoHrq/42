/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:16:34 by nharraqi          #+#    #+#             */
/*   Updated: 2025/02/04 17:46:32 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_strcmpchar(char a, char b);
void	free_and_update_envp(t_ee *ee, int i, char *copy);
int		find_pwd_index(t_ee *ee);
void	check_variable_pwd(t_ee *ee);
char	*ft_strjoin_cd(char *s1, char *s2);

int	ft_strcmpchar(char a, char b)
{
	if (a != b)
		return (1);
	return (0);
}

void	free_and_update_envp(t_ee *ee, int i, char *copy)
{
	if (ee->envp[i])
	{
		if (ft_strcmp(ee->envp[i], ee->copy_pwd) != 0)
		{
			free(ee->envp[i]);
			ee->envp[i] = ft_strdup(copy);
		}
	}
	free(copy);
}

int	find_pwd_index(t_ee *ee)
{
	int	i;
	int	j;

	i = 0;
	while (ee->envp[i])
	{
		j = 0;
		while (ee->envp[i][j])
		{
			if ((ft_strcmpchar(ee->envp[i][j], 'P') == 0)
				&& (ft_strcmpchar(ee->envp[i][j + 1], 'W') == 0)
				&& (ft_strcmpchar(ee->envp[i][j + 2], 'D') == 0))
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	check_variable_pwd(t_ee *ee)
{
	int		i;
	char	*copy;

	i = find_pwd_index(ee);
	if (i == -1)
		return ;
	copy = ft_strjoin_cd("PWD=", ee->copy_pwd);
	if (!copy)
		return ;
	free_and_update_envp(ee, i, copy);
}

char	*ft_strjoin_cd(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
