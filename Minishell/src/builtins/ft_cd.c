/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:25:18 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:25:19 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char *input, t_ee *ee)
{
	t_cd	*cd;

	cd = malloc(sizeof(t_cd));
	am_i_cooked(input, cd, ee);
	if (cd->args[1] == NULL || ft_strcmp(cd->args[0], "~") == 0)
	{
		ee->change_confirmed = 1;
		cd->home = getenv("HOME");
		if (cd->home == NULL || ee->block_home == 1)
		{
			home_is_cooked(cd);
			return ;
		}
		else
			no_inspi_jutsu(cd, ee);
	}
	else
		careful_fire_burns(ee, cd);
	if (cd->result != 0)
	{
		norminette_invocation(cd);
		return ;
	}
	free_split(cd->args);
	free(cd);
}

//////////////////////////////////////////////////////////////////
/*void	check_variable_pwd(t_ee *ee)
{
	int i = 0;
	int j;
	int yes = 0;

	while (ee->envp[i])
	{
		j = 0;
		while (ee->envp[i][j])
		{
			if ((ft_strcmpchar(ee->envp[i][j], 'P') == 0)
				&& (ft_strcmpchar(ee->envp[i][j + 1], 'W') == 0)
				&& (ft_strcmpchar(ee->envp[i][j + 2], 'D') == 0))
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
	char *copy = ft_strjoin_cd("PWD=", ee->copy_pwd);
	if (!copy)
		return ;
	if (ee->envp[i] && ((ft_strcmp(ee->envp[i], ee->copy_pwd) != 0)
			|| (ft_strcmp(ee->envp[i], ee->copy_pwd) == 0)))
	{
		free(ee->envp[i]);
		ee->envp[i] = ft_strdup(copy);
	}
	free(copy);
}*/

/*void	ft_cd(char *input, t_ee *ee)
{
	t_cd *cd;
	int result;

	cd = malloc(sizeof(t_cd));
	input = parse_input_cd(input);
	cd->args = ft_split(input, ' ');
	ee->copy_oldpwd = getcwd(NULL, 0);
	if (cd->args[1] == NULL || ft_strcmp(cd->args[0], "~") == 0)
	{
		ee->change_confirmed = 1;
		cd->home = getenv("HOME");
		if (cd->home == NULL)
		{
			home_is_cooked(cd);
			return ;
		}
		else
		{
			result = chdir(cd->home);
			if (ee->copy_pwd)
				free(ee->copy_pwd);
			ee->copy_pwd = getcwd(NULL, 0);
			check_variable_pwd(ee);
		}
	}
	else
	{
		if (ee->copy_pwd)
			free(ee->copy_pwd);
		if (ee->copy_oldpwd)
			free(ee->copy_oldpwd);
		ee->change_confirmed = 1;
		ee->copy_oldpwd = getcwd(NULL, 0);
		result = chdir(cd->args[1]);
		ee->copy_pwd = getcwd(NULL, 0);
		check_variable_pwd(ee);
	}
	if (result != 0)
	{
		perror("🍂_(´~`)_🍂: cd");
		free_split(cd->args);
		free(cd);
		return ;
	}
	free_split(cd->args);
	free(cd);
}*/
