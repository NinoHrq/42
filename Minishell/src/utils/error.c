/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:32:14 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:01:49 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	gandalf_le_grand_prince(t_redir_handler *hr, char c)
{
	if (c == 'c')
	{
		perror("🔒 Erreur création fichier here-doc");
		redi_pipe_free(hr);
		return ;
	}
	if (c == 'e')
	{
		perror("🔒 Erreur écriture here-doc");
		unlink(hr->heredoc_tmpfile);
		redi_pipe_free(hr);
		return ;
	}
	if (c == 'o')
	{
		perror("🔒 Erreur ouverture fichier here-doc");
		unlink(hr->heredoc_tmpfile);
		redi_pipe_free(hr);
		return ;
	}
	return ;
}

int	handle_error_piperedi(const char *msg, t_pipeline *p, char *input)
{
	perror(msg);
	free_split(p->commands);
	free(input);
	free(p);
	return (-1);
}

int	handle_error(const char *msg, t_pipeline *p, char *input)
{
	perror(msg);
	free_split(p->commands);
	free(input);
	free(p);
	return (-1);
}
