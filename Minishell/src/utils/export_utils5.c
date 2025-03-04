/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:33:58 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:33:59 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	calculate_lengths(t_envv *env, t_ee *ee)
{
	env->len_envp = 0;
	env->len_export = 0;
	if (ee->envp)
	{
		while (ee->envp[env->len_envp])
			env->len_envp++;
	}
	if (ee->copy_export_env)
	{
		while (ee->copy_export_env[env->len_export])
			env->len_export++;
	}
}

char	**allocate_memory(t_envv *env)
{
	return (malloc(sizeof(char *) * (env->len_envp + env->len_export + 1)));
}

bool	copy_env_variables(char **tmp, t_ee *ee, int len_envp)
{
	int	i;

	i = 0;
	while (i < len_envp)
	{
		tmp[i] = ft_strdup(ee->envp[i]);
		if (!tmp[i])
		{
			free_split(tmp);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	copy_export_variables(char **tmp, t_ee *ee, int len_envp,
		int len_export)
{
	int	i;
	int	j;

	i = len_envp;
	j = 0;
	while (j < len_export)
	{
		tmp[i] = ft_strdup(ee->copy_export_env[j]);
		if (!tmp[i])
		{
			free_split(tmp);
			return (false);
		}
		i++;
		j++;
	}
	return (true);
}

char	**copi_colle(t_ee *ee)
{
	t_envv	env;
	char	**tmp;

	calculate_lengths(&env, ee);
	tmp = allocate_memory(&env);
	if (!tmp)
		return (NULL);
	if (!copy_env_variables(tmp, ee, env.len_envp))
		return (NULL);
	if (ee->copy_export_env)
	{
		if (!copy_export_variables(tmp, ee, env.len_envp, env.len_export))
			return (NULL);
	}
	tmp[env.len_envp + env.len_export] = NULL;
	return (tmp);
}

/*char **copi_colle(t_ee *ee)
{
	int len_envp = 0;
	int len_export = 0;
	char **tmp;
	int i = 0;
	int j = 0;

	if (ee->envp)
	{
		while (ee->envp[len_envp])
			len_envp++;
	}
	if (ee->copy_export_env)
	{
		while (ee->copy_export_env[len_export])
			len_export++;
		tmp = malloc(sizeof(char *) * (len_envp + len_export + 1));
		if (!tmp)
			return (NULL);

		while (i < len_envp)
		{
			tmp[i] = ft_strdup(ee->envp[i]);
			if (!tmp[i])
			{
				free_split(tmp);
				return (NULL);
			}
			i++;
		}
		while (j < len_export)
		{
			tmp[i] = ft_strdup(ee->copy_export_env[j]);
			if (!tmp[i])
			{
				free_split(tmp);
				return (NULL);
			}
			i++;
			j++;
		}
	}
	else
	{
		tmp = malloc(sizeof(char *) * (len_envp + 1));
		if (!tmp)
			return (NULL);

		while (i < len_envp)
		{
			tmp[i] = ft_strdup(ee->envp[i]);
			if (!tmp[i])
			{
				free_split(tmp);
				return (NULL);
			}
			i++;
		}
	}
	tmp[i] = NULL;
	return (tmp);
}*/
