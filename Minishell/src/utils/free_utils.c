/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:35:11 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:35:12 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	norminette_backflip(char *final_command, t_redir_handler *hr)
{
	if (!final_command)
	{
		redi_pipe_free(hr);
		return (1);
	}
	redi_last_free(hr);
	return (0);
}

void	cleanup_loop(t_loop *loop)
{
	if (loop)
	{
		if (loop->changed_args)
			free_split(loop->changed_args);
		if (loop->input)
			free(loop->input);
		free(loop);
	}
}

void	close_fds(t_pipeline *p)
{
	if (p->heredoc_fd != -1)
		close(p->heredoc_fd);
	if (p->input_fd != -1)
		close(p->input_fd);
	if (p->output_fd != -1)
		close(p->output_fd);
}

void	close_fds_and_update(t_pipeline *p)
{
	close(p->pipe_fd[1]);
	if (p->prev_fd != -1)
		close(p->prev_fd);
	p->prev_fd = p->pipe_fd[0];
	close_fds(p);
}

void	pid_sup_to_zero_pipe_redi(t_pipeline *p)
{
	close(p->pipe_fd[1]);
	if (p->prev_fd != -1)
		close(p->prev_fd);
	p->prev_fd = p->pipe_fd[0];
	close_fds(p);
	return ;
}
