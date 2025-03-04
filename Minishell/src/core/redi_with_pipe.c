/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_with_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:29:09 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 17:43:39 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_heredoc_redirection(t_redir_handler *hr, t_ee *ee, t_pipeline *p)
{
	int	ret;

	if (hr->heredoc_tmpfile)
		free(hr->heredoc_tmpfile);
	hr->fd = open_available(&hr->heredoc_tmpfile);
	if (hr->fd < 0)
	{
		gandalf_le_grand_prince(hr, 'c');
		return ;
	}
	hr->delimiter = hr->split_in[hr->i + 1];
	ret = write_to_tmpfile(hr->fd, hr->delimiter, ee);
	close(hr->fd);
	if (ret != 0)
	{
		gandalf_le_grand_prince(hr, 'e');
		return ;
	}
	p->heredoc_fd = open(hr->heredoc_tmpfile, O_RDONLY);
	if (p->heredoc_fd < 0)
	{
		gandalf_le_grand_prince(hr, 'o');
		return ;
	}
	hr->i++;
}

void	handle_input_redirection(t_redir_handler *hr, t_pipeline *p)
{
	if (p->input_fd != -1)
		close(p->input_fd);
	p->input_fd = open(hr->split_in[hr->i + 1], O_RDONLY, 0644);
	if (p->input_fd < 0)
	{
		perror("🔒 Erreur ouverture fichier '<'");
		p->breakk = 1;
		return ;
	}
	hr->i++;
}

void	handle_output_redirection(t_redir_handler *hr, t_pipeline *p)
{
	if (p->output_fd != -1)
		close(p->output_fd);
	p->output_fd = open(hr->split_in[hr->i + 1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (p->output_fd < 0)
	{
		perror("🔒 Erreur ouverture fichier '>'");
		p->breakk = 1;
		return ;
	}
	hr->i++;
}

void	handle_append_redirection(t_redir_handler *hr, t_pipeline *p)
{
	if (p->output_fd != -1)
		close(p->output_fd);
	p->output_fd = open(hr->split_in[hr->i + 1], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (p->output_fd < 0)
	{
		perror("🔒 Erreur ouverture fichier '>>'");
		p->breakk = 1;
		return ;
	}
	hr->i++;
}

char	*handle_redi_with_pipe(char *input, t_ee *ee, t_pipeline *p)
{
	t_redir_handler	*hr;
	char			*final_command;

	final_command = NULL;
	hr = malloc(sizeof(t_redir_handler));
	init_p_fd(p);
	init_redir_handler(hr, input);
	while (hr->i < hr->last_name && p->breakk == 0)
	{
		if (ft_strcmp(hr->split_in[hr->i], "<") == 0)
			handle_input_redirection(hr, p);
		else if (ft_strcmp(hr->split_in[hr->i], ">") == 0)
			handle_output_redirection(hr, p);
		else if (ft_strcmp(hr->split_in[hr->i], ">>") == 0)
			handle_append_redirection(hr, p);
		else if (ft_strcmp(hr->split_in[hr->i], "<<") == 0)
			handle_heredoc_redirection(hr, ee, p);
		else
			hr->i++;
	}
	if (hr->input_execv)
		final_command = ft_strdup(hr->input_execv);
	norminette_backflip(final_command, hr);
	return (final_command);
}

/*char *handle_redi_with_pipe(char *input, t_ee *ee, t_pipeline *p)
{
	char **split_in = NULL;
	char *input_execv = NULL;
	int last_name;
	char *path;
	char *final_command;
	t_redir *re = NULL;
	// Here-doc
	char *heredoc_tmpfile = NULL;
	int fd;
	char *delimiter = NULL;

	p->heredoc_fd = -1;
	p->input_fd = -1;
	p->output_fd = -1;

	re = malloc(sizeof(t_redir));
	if (!re)
		return (NULL);
	re->command_fail = 0;
	input_execv = parse_exev_input(input);
	char *tmp = unstick_to_re_stick(input);
	split_in = ft_split(tmp, ' ');
	free(tmp);
	if (!split_in || !split_in[0])
	{
		free_split(split_in);
		free(re);
		free(input_execv);
		return (NULL);
	}
	last_name = ft_strlonglen(split_in);
	path = find_command_path(split_in[0]);
	for (int i = 1; i < last_name; i++)
	{
		if (strcmp(split_in[i], "<<") == 0)
		{
			if (heredoc_tmpfile)
				free(heredoc_tmpfile);
			fd = open_available(&heredoc_tmpfile);
			if (fd < 0)
			{
				perror("🔒 Erreur création fichier here-doc");
				free_split(split_in);
				free(re);
				free(input_execv);
				free(path);
				free(heredoc_tmpfile);
				return (NULL);
			}

			delimiter = split_in[i + 1];
			int ret = write_to_tmpfile(fd, delimiter, ee);
			close(fd);
			if (ret != 0)
			{
				perror("🔒 Erreur écriture here-doc");
				unlink(heredoc_tmpfile);
				free_split(split_in);
				free(re);
				free(input_execv);
				free(path);
				free(heredoc_tmpfile);
				return (NULL);
			}
			p->heredoc_fd = open(heredoc_tmpfile, O_RDONLY);
			if (p->heredoc_fd < 0)
			{
				perror("🔒 Erreur ouverture fichier here-doc");
				unlink(heredoc_tmpfile);
				free_split(split_in);
				free(re);
				free(input_execv);
				free(path);
				free(heredoc_tmpfile);
				return (NULL);
			}
			i++;
		}
		else if (strcmp(split_in[i], "<") == 0)
		{
			p->input_fd = open(split_in[i + 1], O_RDONLY);
			if (p->input_fd < 0)
			{
				perror("🔒 Erreur ouverture fichier '<'");
				free_split(split_in);
				free(re);
				free(input_execv);
				free(path);
				free(heredoc_tmpfile);
				return (NULL);
			}
			i++;
		}
		else if (strcmp(split_in[i], ">") == 0)
		{
			p->output_fd = open(split_in[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
					0777);
			if (p->output_fd < 0)
			{
				perror("🔒 Erreur ouverture fichier '>'");
				free_split(split_in);
				free(re);
				free(input_execv);
				free(path);
				free(heredoc_tmpfile);
				return (NULL);
			}
			i++;
		}
		else if (strcmp(split_in[i], ">>") == 0)
		{
			p->output_fd = open(split_in[i + 1], O_WRONLY | O_CREAT | O_APPEND,
					0777);
			if (p->output_fd < 0)
			{
				perror("🔒 Erreur ouverture fichier '>>'");
				free_split(split_in);
				free(re);
				free(input_execv);
				free(path);
				free(heredoc_tmpfile);
				return (NULL);
			}
			i++;
		}
	}
	final_command = ft_strdup(input_execv);
	if (!final_command)
	{
		free_split(split_in);
		free(re);
		free(input_execv);
		free(path);
		free(heredoc_tmpfile);
		return (NULL);
	}
	free_split(split_in);
	free(input_execv);
	free(path);
	free(re);
	if (heredoc_tmpfile)
	{
		unlink(heredoc_tmpfile);
		free(heredoc_tmpfile);
	}

	return (final_command);
}*/
