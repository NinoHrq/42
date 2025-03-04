/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:48:43 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:48:43 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*complete_tmp(char *src, int i)
{
	int		k;
	int		j;
	char	*tmp;

	k = ft_strlen(src);
	tmp = malloc(sizeof(char) * (k - i + 1));
	if (!tmp)
	{
		free(tmp);
		return (NULL);
	}
	j = 0;
	while (i < k)
	{
		tmp[j] = src[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	if (tmp == NULL)
		free(tmp);
	return (tmp);
}

void	do_what_dq_do(t_ee *ee)
{
	ft_printf("🍁_(`へ´*)_🍁: %d: command not found\n", ee->signal);
	ee->signal = 127;
}
