/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:33:41 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:33:42 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_env_varrrr(char **envp, int len_envp, const char *arg)
{
	size_t	key_len;
	int		j;

	key_len = get_key_length(arg);
	j = 0;
	while (j < len_envp)
	{
		if (strncmp(envp[j], arg, key_len) == 0 && envp[j][key_len] == '=')
			return (j);
		j++;
	}
	return (-1);
}

void	update_env_var(char **envp, int index, const char *arg)
{
	free(envp[index]);
	envp[index] = strdup(arg);
}

void	add_env_var(char ***envp, int *len_envp, const char *arg)
{
	(*envp)[*len_envp] = strdup(arg);
	(*len_envp)++;
	(*envp)[*len_envp] = NULL;
}

void	handle_env_with_equals(char **args, char ***copy_envp, int *len_envp)
{
	int	i;
	int	index;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '=')
		{
			print_invalid_identifier(args[i]);
			i++;
			continue ;
		}
		if (strchr(args[i], '=') && args[i][0] != '=')
		{
			index = find_env_varrrr(*copy_envp, *len_envp, args[i]);
			if (index != -1)
				update_env_var(*copy_envp, index, args[i]);
			else
				add_env_var(copy_envp, len_envp, args[i]);
		}
		i++;
	}
}

/*void handle_env_with_equals(char **args, char ***copy_envp, int *len_envp)
{
	int i = 1;
	int found;
	int j;
	size_t key_len;

	while (args[i])
	{
		if (args[i][0] == '=')
		{
			ft_printf("🔥_(╬ Ò﹏Ó)_🔥: export: %s: not a valid identifier\n",
				args[i]);
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '=') && args[i][0] != '=')
		{
			found = 0;
			j = 0;
			while (j < *len_envp)
			{
				key_len = ft_strchr(args[i], '=') - args[i];
				if (ft_strncmp((*copy_envp)[j], args[i], key_len) == 0
					&& (*copy_envp)[j][key_len] == '=')
				{
					free((*copy_envp)[j]);
					(*copy_envp)[j] = ft_strdup(args[i]);
					found = 1;
					break ;
				}
				j++;
			}
			if (!found)
			{
				(*copy_envp)[*len_envp] = ft_strdup(args[i]);
				(*len_envp)++;
				(*copy_envp)[*len_envp] = NULL;
			}
		}
		i++;
	}
}*/
