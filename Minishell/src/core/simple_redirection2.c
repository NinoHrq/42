/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redirection2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:29:23 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 16:38:35 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norminette_frontflip(t_ee *ee, t_redir_simple *hr)
{
	ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", hr->split_in[0]);
	ee->signal = 127;
	ee->confirmed_command = 0;
}

void	handle_redirection(char *input, t_ee *ee)
{
	t_redir_simple	*hr;

	hr = init_redirr_handler(input);
	if (!hr)
		return ;
	if (fork_and_execute(hr, ee) == -1)
		return ;
	free_at_last(hr);
}

int	fork_and_execute(t_redir_simple *hr, t_ee *ee)
{
	hr->pid = fork();
	if (hr->pid == -1)
	{
		free_if_pid_is_n(hr);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (hr->pid == 0)
		handle_child_simple_process(hr, ee);
	else
		handle_parent_process(hr, ee);
	return (0);
}

void	handle_child_simple_process(t_redir_simple *hr, t_ee *ee)
{
	if (handle_heredoc(hr, ee) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	handle_otpt_redirection(hr);
	cumulate_token(hr->input_execv, ee);
	exit(EXIT_SUCCESS);
}

void	handle_parent_process(t_redir_simple *hr, t_ee *ee)
{
	waitpid(hr->pid, &hr->status, 0);
	if (WIFEXITED(hr->status))
	{
		ee->signal = WEXITSTATUS(hr->status);
		if (ee->signal != 0 && ee->signal != 1)
			ee->signal = 128 + ee->signal;
	}
	if (!hr->path)
		norminette_frontflip(ee, hr);
	else
	{
		if (ee->signal != 1)
			ee->confirmed_command = 1;
	}
	signal(SIGINT, handle_sigint);
}
