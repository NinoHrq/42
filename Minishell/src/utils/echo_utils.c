/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:37:14 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/08 12:26:29 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_tmp_value(char **tmp)
{
	int		i;
	int		j;
	int		total_len;
	char	*t;
	int		k;

	total_len = 0;
	i = 1;
	while (tmp[i])
		total_len += strlen(tmp[i++]);
	t = malloc(sizeof(char) * (total_len + 1));
	if (!t)
		return ;
	i = 1;
	j = 0;
	while (tmp[i])
	{
		k = 0;
		while (tmp[i][k])
			t[j++] = tmp[i][k++];
		i++;
	}
	t[j] = '\0';
	tmp[1] = t;
}

char	*find_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (str);
		str++;
	}
	return (NULL);
}

void	replace_dollar(t_parser *p, char ***input, t_ee *ee)
{
	p->tmp = find_dollar((*input)[p->i]);
	if (!p->tmp)
		return ;
	p->j = p->tmp - (*input)[p->i];
	p->kekw = get_env_value(p->tmp + 1, ee);
	if (!p->kekw)
	{
		(*input)[p->i][p->j] = '\0';
		return ;
	}
	p->new_len = ft_strlen((*input)[p->i]) - ft_strlen(p->tmp)
		+ ft_strlen(p->kekw);
	p->new_value = malloc(sizeof(char) * (p->new_len + 1));
	if (!p->new_value)
		return ;
	strncpy(p->new_value, (*input)[p->i], p->j);
	p->new_value[p->j] = '\0';
	strcat(p->new_value, p->kekw);
	strcat(p->new_value, p->tmp + ft_strlen(p->tmp));
	free((*input)[p->i]);
	(*input)[p->i] = p->new_value;
	free(p->kekw);
}

void	parse_dollars_input(char ***input, t_ee *ee)
{
	t_parser	p;

	p.i = 0;
	while ((*input)[p.i])
	{
		if (f_sq((*input)[p.i]) == 0)
		{
			p.j = 0;
			while ((*input)[p.i][p.j])
			{
				if ((*input)[p.i][p.j] == '$')
				{
					replace_dollar(&p, input, ee);
					return ;
				}
				p.j++;
			}
		}
		p.i++;
	}
}
