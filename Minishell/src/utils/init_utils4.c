/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:02:39 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 16:44:24 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_p_fd(t_pipeline *p)
{
	p->breakk = 0;
	p->heredoc_fd = -1;
	p->input_fd = -1;
	p->output_fd = -1;
}

int	i_want_to_sing_a_song_hiihi(t_redir_handler *hr)
{
	if (!hr->split_in || !hr->split_in[0])
	{
		free(hr->tmp);
		free_split(hr->split_in);
		return (1);
	}
	return (0);
}

void	init_parser(t_pparser *p)
{
	p->i = 0;
	p->j = 0;
	p->quote = '\0';
	p->return_input = NULL;
}
