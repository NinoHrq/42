/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redirection3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:29:37 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 18:26:34 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_output_file(t_redir_simple *hr, char *filename, int flags)
{
	hr->file = open(filename, flags, 0777);
	if (hr->file == -1)
	{
		perror("🔒 Erreur ouverture fichier de redirection");
		exit(EXIT_FAILURE);
	}
	dup2(hr->file, STDOUT_FILENO);
	close(hr->file);
}

void	open_input_file(t_redir_simple *hr, char *filename)
{
	hr->file = open(filename, O_RDONLY);
	if (hr->file == -1)
	{
		perror("🔒 Erreur ouverture fichier de redirection");
		exit(EXIT_FAILURE);
	}
	dup2(hr->file, STDIN_FILENO);
	close(hr->file);
}

void	redirect_output(t_redir_simple *hr)
{
	int	i;

	i = 1;
	while (i < hr->last_name)
	{
		if (ft_strcmp(hr->split_in[i], ">") == 0)
		{
			open_output_file(hr, hr->split_in[i + 1],
				O_WRONLY | O_CREAT | O_TRUNC);
			i++;
		}
		else if (ft_strcmp(hr->split_in[i], "<") == 0)
		{
			open_input_file(hr, hr->split_in[i + 1]);
			i++;
		}
		else if (ft_strcmp(hr->split_in[i], ">>") == 0)
		{
			open_output_file(hr, hr->split_in[i + 1],
				O_WRONLY | O_CREAT | O_APPEND);
			i++;
		}
		i++;
	}
}

void	handle_otpt_redirection(t_redir_simple *hr)
{
	redirect_output(hr);
}
