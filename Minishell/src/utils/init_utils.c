/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:01 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/04 16:37:36 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_when_heredoc_at_start(t_redir_simple *hr, char *input)
{
	hr->input_execv = parse_exev_input(input);
	hr->if_need_sep = unstick_to_re_stick(input);
	hr->split_execv = ft_split(hr->input_execv, ' ');
	hr->split_in = ft_split(hr->if_need_sep, ' ');
	if (!hr->split_in || !hr->split_in[0])
	{
		free_if_simple_redir_fail(hr);
		return ;
	}
	hr->last_name = ft_strlonglen(hr->split_in);
	hr->path = find_command_path(hr->input_execv);
	hr->heredoc_tmpfile = NULL;
	hr->heredoc_fd = -1;
	hr->heredoc_count = 0;
	if (found_only_one_redirection(input) == 1)
		hr->help = 1;
	else
		hr->help = 0;
	hr->delimiter = NULL;
}

void	norminette_nosegrind(t_redir_simple *hr, char *input)
{
	hr->input_execv = parse_exev_input(input);
	hr->if_need_sep = unstick_to_re_stick(input);
	hr->split_execv = ft_splittt(hr->input_execv, ' ');
	hr->split_in = ft_splittt(hr->if_need_sep, ' ');
	if (!hr->split_execv || !hr->split_execv[0] || !hr->split_in
		|| !hr->split_in[0])
	{
		free_if_simple_redir_fail(hr);
		return ;
	}
	hr->last_name = ft_strlonglen(hr->split_in);
	hr->path = find_command_path(hr->split_in[0]);
	hr->heredoc_tmpfile = NULL;
	hr->heredoc_fd = -1;
	hr->heredoc_count = 0;
	hr->help = 0;
	hr->delimiter = NULL;
}

t_redir_simple	*init_redirr_handler(char *input)
{
	t_redir_simple	*hr;

	hr = malloc(sizeof(t_redir_simple));
	if (!hr)
		return (NULL);
	if (input[0] == '<' && input[1] == '<')
		init_when_heredoc_at_start(hr, input);
	else
		norminette_nosegrind(hr, input);
	return (hr);
}

/*t_redir_simple	*init_redirr_handler(char *input)
{
	t_redir_simple	*hr;

	hr = malloc(sizeof(t_redir_simple));
	if (!hr)
		return (NULL);
	if (input[0] == '<' && input[1] == '<')
		init_when_heredoc_at_start(hr, input);
	else
	{
		hr->input_execv = parse_exev_input(input);
		hr->if_need_sep = unstick_to_re_stick(input);
		hr->split_execv = ft_split(hr->input_execv, ' ');
		hr->split_in = ft_split(hr->if_need_sep, ' ');
		if (!hr->split_execv || !hr->split_execv[0] || !hr->split_in
			|| !hr->split_in[0])
		{
			free_if_simple_redir_fail(hr);
			return (NULL);
		}
		hr->last_name = ft_strlonglen(hr->split_in);
		hr->path = find_command_path(hr->split_in[0]);
		hr->heredoc_tmpfile = NULL;
		hr->heredoc_fd = -1;
		hr->heredoc_count = 0;
		hr->help = 0;
		hr->delimiter = NULL;
	}
	return (hr);
}*/

void	init_redir_handler(t_redir_handler *handler, char *input)
{
	handler->tmp = unstick_to_re_stick(input);
	if (!handler->tmp)
		return ;
	handler->split_in = ft_split(handler->tmp, ' ');
	if (i_want_to_sing_a_song_hiihi(handler))
		return ;
	handler->split_execv = NULL;
	handler->last_name = ft_strlonglen(handler->split_in);
	handler->file = -1;
	handler->pid = 0;
	handler->input_execv = parse_exev_input(input);
	handler->path = find_command_path(handler->split_in[0]);
	handler->heredoc_tmpfile = NULL;
	handler->heredoc_fd = -1;
	handler->delimiter = NULL;
	handler->heredoc_count = 0;
	handler->fd = -1;
	handler->status = 0;
	handler->i = 1;
	handler->re = malloc(sizeof(t_redir));
	if (!handler->re)
		return ;
	handler->re->command_fail = 0;
}

void	init_value_token(t_token *token, char *input)
{
	token->token = 0;
	token->trimmed_input = NULL;
	token->trimmed_input = skip_isspace_for_fonctions(input, token);
	if (!token->trimmed_input)
	{
		if (token)
			free(token);
		return ;
	}
	return ;
}
