/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:01:22 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 19:01:22 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_heredoc(t_redir_simple *hr)
{
	hr->heredoc_fd = open_available(&hr->heredoc_tmpfile);
	if (hr->heredoc_fd < 0)
	{
		perror("🔒 Erreur création fichier temporaire here-doc");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_redir_simple *hr, t_ee *ee)
{
	if (init_heredoc(hr) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_heredoc_entries(hr, ee) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (finalize_heredoc(hr) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
