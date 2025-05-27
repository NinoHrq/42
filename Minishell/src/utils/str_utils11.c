/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:45:57 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 17:49:10 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_freetableautt(char **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	tableau_picasso(t_tableautt *tt)
{
	tt->i = 0;
	tt->j = 0;
	tt->in_quotes = 0;
}

void	skip_separators(const char *str, char sep, t_tableautt *tt)
{
	while (str[tt->i] && str[tt->i] == sep)
		tt->i++;
}

void	skip_quoted_part(char *tmp_in, t_pparser *p)
{
	p->quote = tmp_in[p->i++];
	while (tmp_in[p->i] && tmp_in[p->i] != p->quote)
		p->i++;
	if (tmp_in[p->i] == p->quote)
		p->i++;
}

int	black_hole(char *tmp, t_ee *ee)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] <= 32)
		i++;
	if (tmp[i] == '\0')
	{
		ee->signal = 0;
		return (1);
	}
	return (0);
}
