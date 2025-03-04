/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:11 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:36:12 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_ls(t_ls *ls, char *input)
{
	ls->args = ft_split(input, ' ');
	ls->file_found = 0;
	if (ls->args[1] == NULL)
		ls->path = ".";
	else
		ls->path = ls->args[1];
}

char	*parse_input_ls(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' && input[i + 1] == '\0')
		{
			input[i] = '\0';
			break ;
		}
		if (input[i] == ';' && input[i + 1] != '\0')
		{
			input[i] = '\0';
			break ;
		}
		if (input[i] == ';' && (input[i - 1] != ' '))
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	return (input);
}

void	clean_up_ls(t_ls *ls)
{
	if (ls->args)
		free_split(ls->args);
	if (ls->dir)
		closedir(ls->dir);
}
