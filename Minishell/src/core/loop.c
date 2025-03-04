/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:28:44 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 16:55:14 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	more_parse_and_assign(t_loop *loop, t_ee *ee)
{
	if (g_status == 130)
	{
		ee->signal = 130;
		g_status = 0;
	}
	loop->input = handle_unclosed_quotes(loop->input, ee);
	if (!loop->input || !*loop->input)
	{
		cleanup_loop(loop);
		return (1);
	}
	return (0);
}

int	processe_and_do_input(t_loop *loop, t_ee *ee)
{
	if (find_trap(loop->input))
	{
		cleanup_loop(loop);
		return (1);
	}
	cumulate_token(loop->input, ee);
	cleanup_loop(loop);
	return (0);
}

int	all_what_is_need(char *tmp, t_loop *loop, t_ee *ee)
{
	if (check_tmp_not_null(tmp, ee))
	{
		free(loop);
		return (1);
	}
	add_history(tmp);
	if (ft_strcmp(tmp, "echo$?") == 0)
	{
		ft_printf("🍁_(`へ´*)_🍁: echo%d: command not found\n", ee->signal);
		free(loop);
		free(tmp);
		return (1);
	}
	if (parse_tmp(tmp, loop, ee))
		return (1);
	if (more_parse_and_assign(loop, ee))
		return (1);
	signal(SIGQUIT, handle_sigquit);
	if (processe_and_do_input(loop, ee))
		return (1);
	free(tmp);
	return (0);
}

void	loop(char *tmp, t_ee *ee)
{
	t_loop	*loop;

	if ((!ee->envp || !ee->envp[0]) && ee->lock_path == 0)
		you_shall_not_path();
	loop = malloc(sizeof(t_loop));
	if (!loop)
		return ;
	init_struct_loop(loop);
	signal(SIGQUIT, SIG_IGN);
	tmp = readline("🍀_(^o^)_🍀  > ");
	if (all_what_is_need(tmp, loop, ee))
		return ;
	return ;
}
