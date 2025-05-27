/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:37:37 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 20:39:34 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_status = 130;
	}
}

void	catch_signal(t_ee *ee)
{
	(void)ee;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_herdoc_sigint(int status)
{
	rl_replace_line("", 0);
	ft_putendl_fd("\n", 1);
	rl_on_new_line();
	unlink("/tmp/heredoc_tmp");
	exit(status);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_printf("Quit signal received (Ctrl+\\)\n");
}

void	check_signal(char *command, t_ee *ee)
{
	if (ft_strcmp(command, "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		ee->reset_sigint = 1;
	}
}
