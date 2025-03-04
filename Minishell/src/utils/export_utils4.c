/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:33:49 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:33:50 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_export_var(char **export_list, int len_export, const char *arg)
{
	int		j;
	char	*current_name;
	int		found;

	j = 0;
	while (j < len_export)
	{
		current_name = strndup(export_list[j], strchr(export_list[j], '=')
				- export_list[j]);
		found = strcmp(current_name, arg) == 0;
		free(current_name);
		if (found)
			return (j);
		j++;
	}
	return (-1);
}

void	add_export_var(char ***export_list, int *len_export, const char *arg)
{
	(*export_list)[*len_export] = strdup(arg);
	(*len_export)++;
	(*export_list)[*len_export] = NULL;
}

void	handle_export_without_equals(char **args, char ***copy_export,
		int *len_export)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		if (find_export_var(*copy_export, *len_export, args[i]) == -1)
			add_export_var(copy_export, len_export, args[i]);
		i++;
	}
}

/*void handle_export_without_equals(char **args, char ***copy_export,
	int *len_export)
{
	int i = 1;
	while (args[i])
	{
		if (ft_check_equal(args[i]))
		{
			i++;
			continue ;
		}
		int found = 0;
		int j = 0;
		while (j < *len_export)
		{
			char *current_name = ft_strndup((*copy_export)[j],
					ft_strchr((*copy_export)[j], '=') - (*copy_export)[j]);
			if (ft_strcmp(current_name, args[i]) == 0)
			{
				found = 1;
				free(current_name);
				break ;
			}
			free(current_name);
			j++;
		}
		if (!found)
		{
			(*copy_export)[*len_export] = ft_strdup(args[i]);
			(*len_export)++;
			(*copy_export)[*len_export] = NULL;
		}
		i++;
	}
}*/
