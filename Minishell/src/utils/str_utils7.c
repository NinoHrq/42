/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:53:17 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:51:12 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	verif_what_after_redirection_utils(char *input, int *i)
{
	while (input[*i])
	{
		if ((input[*i] == '<' || input[*i] == '>') && (input[*i + 1] == '<'
				|| input[*i + 1] == '>'))
		{
			(*i) += 2;
			break ;
		}
		else if (input[*i] == '<' || input[*i] == '>')
		{
			(*i) += 1;
			break ;
		}
		(*i)++;
	}
}

int	verif_what_after_redirection(char *input, t_ee *ee)
{
	int	i;

	i = 0;
	verif_what_after_redirection_utils(input, &i);
	while (input[i] && input[i] <= 32)
		i++;
	if (input[i] == '<' || input[i] == '>' || input[i] == '|' || input[i] == ';'
		|| input[i] == '&')
	{
		ee->signal = 2;
		return (1);
	}
	return (0);
}

int	parse_tmp(char *tmp, t_loop *loop, t_ee *ee)
{
	if (check_syntax_error(tmp, ee) || check_unexpected_semicolon(tmp, ee)
		|| check_for_no_double(tmp, ee) || verif_what_after_redirection(tmp, ee)
		|| *tmp == '\0')
	{
		free(tmp);
		cleanup_loop(loop);
		return (1);
	}
	loop->input = cut_for_no_leaks_at_the_end(tmp);
	if (!loop->input)
	{
		free(tmp);
		cleanup_loop(loop);
		return (1);
	}
	return (0);
}

char	*parse_final_command(char *input)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (input[i] && input[i] <= 32)
		i++;
	if (input[i] == '\0')
	{
		free(input);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(input + i) + 1));
	if (!tmp)
		return (NULL);
	while (input[i])
		tmp[j++] = input[i++];
	tmp[j] = '\0';
	free(input);
	return (tmp);
}

char	*parse_env_value(char *value)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	j = 0;
	i = ft_strlen(value) - 1;
	while (value[i] <= 32)
		i--;
	tmp = malloc(sizeof(char) * (i + 2));
	while (j <= i)
	{
		tmp[j] = value[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}
