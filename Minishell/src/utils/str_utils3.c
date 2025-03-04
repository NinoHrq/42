/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:38:15 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:38:16 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_pipe(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|' && (input[i + 1] != '|'))
			return (1);
		if (input[i] == '|' && input[i + 1] == '|')
			return (0);
		i++;
	}
	return (0);
}

void	for_norminette(t_ee *ee)
{
	printf("🛠️_(>_<;)_🛠️   : syntax error near unexpected token `&'\n");
	ee->signal = 2;
}

int	check_tmp_not_null(char *tmp, t_ee *ee)
{
	if (tmp == NULL)
	{
		ee->minishell_check = 1;
		free(tmp);
		return (1);
	}
	return (0);
}

int	skip_whitespace(const char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] <= 32)
		i++;
	return (i);
}

int	skip_whitespacee(const char *tmp, int i)
{
	while (tmp[i] && tmp[i] <= 32)
		i++;
	return (i);
}
