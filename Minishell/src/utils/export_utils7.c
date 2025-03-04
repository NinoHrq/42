/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:17 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:34:18 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	count_env_length(t_rdp *rdp, char **env)
{
	while (env[rdp->len_env])
		rdp->len_env++;
}

void	allocate_to_keep(t_rdp *rdp)
{
	rdp->to_keep = malloc(sizeof(int) * rdp->len_env);
	if (rdp->to_keep)
	{
		rdp->i = 0;
		while (rdp->i < rdp->len_env)
		{
			rdp->to_keep[rdp->i] = 1;
			rdp->i++;
		}
	}
}

void	remove_duplicates(t_rdp *rdp, char **env)
{
	rdp->i = 0;
	while (rdp->i < rdp->len_env)
	{
		if (!rdp->to_keep[rdp->i])
		{
			rdp->i++;
			continue ;
		}
		rdp->j = rdp->i + 1;
		while (rdp->j < rdp->len_env)
		{
			assign_rdp_name(rdp, env);
			if (ft_strcmp(rdp->name_i, rdp->name_j) == 0)
			{
				if (ft_strchr(env[rdp->j], '='))
					rdp->to_keep[rdp->i] = 0;
				else
					rdp->to_keep[rdp->j] = 0;
			}
			free(rdp->name_i);
			free(rdp->name_j);
			rdp->j++;
		}
		rdp->i++;
	}
}

char	**copy_filtered_env(t_rdp *rdp, char **env)
{
	if (!rdp->result)
		return (NULL);
	rdp->i = 0;
	rdp->k = 0;
	while (rdp->i < rdp->len_env)
	{
		if (rdp->to_keep[rdp->i])
		{
			rdp->result[rdp->k] = ft_strdup(env[rdp->i]);
			if (!rdp->result[rdp->k])
			{
				free_split(rdp->result);
				free(rdp->to_keep);
				return (NULL);
			}
			rdp->k++;
		}
		rdp->i++;
	}
	rdp->result[rdp->k] = NULL;
	free(rdp->to_keep);
	return (rdp->result);
}

char	**remove_duplicates_with_priority(char **env)
{
	t_rdp	rdp;

	initialize_rdp(&rdp);
	count_env_length(&rdp, env);
	allocate_to_keep(&rdp);
	if (!rdp.to_keep)
		return (NULL);
	remove_duplicates(&rdp, env);
	allocate_result(&rdp);
	return (copy_filtered_env(&rdp, env));
}

/*char **remove_duplicates_with_priority(char **env)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int len_env = 0;
	int *to_keep;
	char **result;
	size_t name_i_len = 0;
	size_t name_j_len = 0;
	char *name_i;
	char *name_j;
	int new_len;

	while (env[len_env])
		len_env++;
	to_keep = malloc(sizeof(int) * len_env);
	if (!to_keep)
		return (NULL);
	while (i < len_env)
	{
		to_keep[i] = 1;
		i++;
	}
	i = 0;
	while (i < len_env)
	{
		if (!to_keep[i])
		{
			i++;
			continue ;
		}
		j = i + 1;
		while (j < len_env)
		{
			name_i_len = 0;
			name_j_len = 0;
			while (env[i][name_i_len] && env[i][name_i_len] != '=')
				name_i_len++;
			while (env[j][name_j_len] && env[j][name_j_len] != '=')
				name_j_len++;
			name_i = ft_strndup(env[i], name_i_len);
			name_j = ft_strndup(env[j], name_j_len);
			if (ft_strcmp(name_i, name_j) == 0)
			{
				if (ft_strchr(env[j], '='))
				{
					to_keep[i] = 0;
					free(name_i);
					free(name_j);
					break ;
				}
				else
					to_keep[j] = 0;
			}
			free(name_i);
			free(name_j);
			j++;
		}
		i++;
	}
	new_len = 0;
	i = 0;
	while (i < len_env)
	{
		if (to_keep[i])
			new_len++;
		i++;
	}
	result = malloc(sizeof(char *) * (new_len + 1));
	if (!result)
	{
		free(to_keep);
		return (NULL);
	}
	i = 0;
	k = 0;
	while (i < len_env)
	{
		if (to_keep[i])
		{
			result[k] = ft_strdup(env[i]);
			if (!result[k])
			{
				free_split(result);
				free(to_keep);
				return (NULL);
			}
			k++;
		}
		i++;
	}
	result[k] = NULL;
	free(to_keep);
	return (result);
}*/
