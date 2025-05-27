/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:38:03 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 21:04:24 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//////////////////////////////////////////////////////////////////////
char	*ft_stcatt(char c, const char *str)
{
	int		len;
	char	*new_str;

	len = strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	new_str[0] = c;
	strcpy(new_str + 1, str);
	return (new_str);
}

///
int	f_q(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

///
void	for_quote_at_start(char ***args)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (args[i][j])
	{
		if (f_q(args[i][j]) == 1)
		{
			new_str = ft_stcatt('"', args[i][j]);
			free(args[i][j]);
			args[i][j] = new_str;
		}
		j++;
	}
	return ;
}

char	**check_dollars(char *input, t_ee *ee)
{
	char	**args;
	int		i;

	args = ft_splittt(input, ' ');
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "$OLDPWD") == 0)
		{
			free(args[i]);
			if (ee->copy_oldpwd)
				args[i] = ft_strdup(ee->copy_oldpwd);
			else
				args[i] = ft_strdup("");
			if (!args[i])
			{
				free_split(args);
				return (NULL);
			}
		}
		i++;
	}
	return (args);
}

char	*remove_parentheses(char *input)
{
	t_parentheses_remover	r;
	int						j;

	init_remover(&r, input);
	if (!r.tmp)
		return (NULL);
	j = ft_strlen(input);
	while (input[r.i] && r.i < j)
	{
		if (r.i > 0 && input[r.i - 1] == '(' && r.level++ > 0)
			r.tmp[r.j++] = input[r.i];
		else if (input[r.i] == ')' && --r.level > 0)
			r.tmp[r.j++] = input[r.i];
		else if (r.level > 0 || input[r.i] != ')')
		{
			if (input[r.i] == '(')
				r.i++;
			r.tmp[r.j++] = input[r.i];
		}
		r.i++;
	}
	r.tmp[r.j] = '\0';
	return (r.tmp);
}
