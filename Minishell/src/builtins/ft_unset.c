/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:27:08 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:27:14 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_variable_from_envp(t_unset_data *data, t_ee *ee)
{
	data->i = 0;
	data->k = 0;
	while (ee->envp && ee->envp[data->i])
	{
		data->skip = 0;
		data->j = 1;
		while (data->args[data->j])
		{
			data->len = ft_strlen(data->args[data->j]);
			if (ft_strncmp(ee->envp[data->i], data->args[data->j],
					data->len) == 0 && ee->envp[data->i][data->len] == '=')
			{
				if (ft_strcmp("PATH", data->args[data->j]) == 0)
					norminette_pop_shove_it(ee);
				data->skip = 1;
				break ;
			}
			data->j++;
		}
		if (!data->skip)
			norminette_hardflip(data, ee);
		data->i++;
	}
	data->new_envp[data->k] = NULL;
}

void	update_env_flags(t_unset_data *data, t_ee *ee)
{
	data->i = 1;
	while (data->args[data->i])
	{
		if (ft_strcmp(data->args[data->i], "PWD") == 0)
			ee->if_unset__pwd = 1;
		if (ft_strcmp(data->args[data->i], "OLDPWD") == 0)
			ee->if_unset__oldpwd = 1;
		if (ft_strcmp(data->args[data->i], "SHLVL") == 0)
			ee->if_unset__shlvl = 1;
		data->i++;
	}
}

void	remove_and_free_unset(t_unset_data data, t_ee *ee)
{
	if (!ee->envp)
	{
		free_split(data.args);
		return ;
	}
	data.new_envp = malloc(sizeof(char *) * (ft_strlonglen(ee->envp) + 1));
	if (!data.new_envp)
	{
		free_split(data.args);
		return ;
	}
	remove_variable_from_envp(&data, ee);
	if (ee->envp)
		free_split(ee->envp);
	ee->envp = data.new_envp;
	update_env_flags(&data, ee);
	if (data.args)
		free_split(data.args);
}

void	ft_unset(char *input, t_ee *ee)
{
	t_unset_data	dt;

	dt.args = ft_split(input, ' ');
	if (!dt.args || !dt.args[1])
	{
		free_split(dt.args);
		return ;
	}
	dt.i = 1;
	while (dt.args[dt.i])
	{
		if (ft_strcmp(dt.args[dt.i], "PATH") == 0)
			norminette_heelflip(ee);
		else if (ft_strcmp(dt.args[dt.i], "HOME") == 0)
			ee->block_home = 1;
		dt.i++;
	}
	remove_and_free_unset(dt, ee);
}

/////////////////////////////////////////////////////////////
/*void	ft_unset(char *input, t_ee *ee)
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
			if (ft_strncmp(ee->envp[i], args[j], len) == 0
				&& ee->envp[i][len] == '=')
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
}*/
