/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:35:32 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:35:33 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_quote_handler(t_quote_handler *qh)
{
	qh->size = 1024;
	qh->i = 0;
	qh->j = 0;
	qh->quote = '\0';
	qh->expanded = NULL;
	qh->expanded_len = 0;
	qh->result = malloc(qh->size);
}

void	init_remover(t_parentheses_remover *r, char *input)
{
	r->i = 0;
	r->j = 0;
	r->level = 0;
	r->tmp = malloc(sizeof(char) * (strlen(input) + 1));
}

void	init_quote_struct(t_quote *qt)
{
	qt->single_quotes = 0;
	qt->double_quotes = 0;
	qt->temp = NULL;
	qt->next_line = NULL;
}

void	init_pipe_struct(t_pipe *pipe)
{
	pipe->commands = NULL;
	pipe->prev_fd = -1;
	pipe->i = 0;
	pipe->pid = 0;
}

void	init_struct_loop(t_loop *loop)
{
	loop->changed_args = NULL;
	loop->cleaned_input = NULL;
	loop->input = NULL;
}
