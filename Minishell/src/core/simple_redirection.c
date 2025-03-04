/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:29:46 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 19:46:15 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	finalize_heredoc(t_redir_simple *hr)
{
	hr->heredoc_fd = open(hr->heredoc_tmpfile, O_RDONLY);
	if (hr->heredoc_fd < 0)
	{
		perror("🔒 Erreur ouverture fichier here-doc final");
		return (EXIT_FAILURE);
	}
	dup2(hr->heredoc_fd, STDIN_FILENO);
	close(hr->heredoc_fd);
	unlink(hr->heredoc_tmpfile);
	return (EXIT_SUCCESS);
}

int	read_and_write_heredoc(t_redir_simple *hr, char *buffer)
{
	ssize_t	bytes;

	hr->fd = open(hr->tmpfilenames[hr->heredoc_count], O_RDONLY);
	if (hr->fd < 0)
	{
		perror("🔒 Erreur ouverture fichier here-doc");
		unlink(hr->tmpfilenames[hr->heredoc_count]);
		return (EXIT_FAILURE);
	}
	bytes = read(hr->fd, buffer, sizeof(buffer));
	while (bytes > 0)
	{
		write(hr->heredoc_fd, buffer, bytes);
		bytes = read(hr->fd, buffer, sizeof(buffer));
	}
	close(hr->fd);
	unlink(hr->tmpfilenames[hr->heredoc_count]);
	return (EXIT_SUCCESS);
}
//////////////////////////////////////////////////////////////

int	process_single_heredoc(t_redir_simple *hr, t_ee *ee, char *buffer)
{
	hr->fd = open_available(&hr->tmpfilenames[hr->heredoc_count]);
	if (hr->fd < 0)
		return (perror("🔒 Erreur création fichier here-doc"), EXIT_FAILURE);
	write_to_tmpfile(hr->fd, hr->delimiter, ee);
	close(hr->fd);
	if (read_and_write_heredoc(hr, buffer) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	hr->heredoc_count++;
	return (EXIT_SUCCESS);
}

int	process_multiple_heredocs(t_redir_simple *hr, t_ee *ee, char *buffer)
{
	int	i;

	i = 1;
	while (i < hr->last_name)
	{
		if (ft_strcmp(hr->split_in[i], "<<") == 0)
		{
			hr->fd = open_available(&hr->tmpfilenames[hr->heredoc_count]);
			if (hr->fd < 0)
				return (perror("🔒 Erreur création fichier here-doc"),
					EXIT_FAILURE);
			hr->delimiter = hr->split_in[i + 1];
			write_to_tmpfile(hr->fd, hr->delimiter, ee);
			close(hr->fd);
			if (read_and_write_heredoc(hr, buffer) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			hr->heredoc_count++;
			i++;
		}
		i++;
	}
	close(hr->heredoc_fd);
	return (EXIT_SUCCESS);
}

int	process_heredoc_entries(t_redir_simple *hr, t_ee *ee)
{
	char	buffer[1024];

	if (hr->help == 1)
	{
		hr->delimiter = hr->split_in[1];
		return (process_single_heredoc(hr, ee, buffer));
	}
	else
	{
		return (process_multiple_heredocs(hr, ee, buffer));
	}
}

//////////////////////////////////////////////////////////
/*int	process_heredoc_entries(t_redir_simple *hr, t_ee *ee)
{
	char	buffer[1024];
	int		i;

	if (hr->help == 1)
	{
		hr->delimiter = hr->split_in[1];
		hr->fd = open_available(&hr->tmpfilenames[hr->heredoc_count]);
		if (hr->fd < 0)
			return (perror("🔒 Erreur création fichier here-doc"), EXIT_FAILURE);
		write_to_tmpfile(hr->fd, hr->delimiter, ee);
		close(hr->fd);
		if (read_and_write_heredoc(hr, buffer) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		hr->heredoc_count++;
		return (EXIT_SUCCESS);
	}
	else
	{
		i = 1;
		while (i < hr->last_name)
		{
			if (strcmp(hr->split_in[i], "<<") == 0)
			{
				hr->fd = open_available(&hr->tmpfilenames[hr->heredoc_count]);
				if (hr->fd < 0)
					return (perror("🔒 Erreur création fichier here-doc"),
						EXIT_FAILURE);
				hr->delimiter = hr->split_in[i + 1];
				write_to_tmpfile(hr->fd, hr->delimiter, ee);
				close(hr->fd);
				if (read_and_write_heredoc(hr, buffer) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				hr->heredoc_count++;
				i++;
			}
			i++;
		}
		close(hr->heredoc_fd);
	}
	return (EXIT_SUCCESS);
}*/

/*void	handle_redirection(char *input, t_ee *ee)
{
	char	*tmp_in;
	char	*if_need_sep;
	char	**split_in;
	int		last_name;
	int		file;
	pid_t	pid;
	char	*path;
	char	*input_execv;
	char	**split_execv;
	t_redir	*re;
	char	*heredoc_tmpfile;
	int		heredoc_fd;
	char	*tmpfilenames[10];
	int		heredoc_count;
	int		fd;
	int		status;
	char	*delimiter;
	int		ret;
				char buffer[1024];
				ssize_t bytes;

	split_in = NULL;
	file = -1;
	input_execv = NULL;
	split_execv = NULL;
	re = NULL;
	// here-doc
	heredoc_tmpfile = NULL;
	heredoc_fd = -1;
	heredoc_count = 0;
	delimiter = NULL;
	re = malloc(sizeof(t_redir));
	if (!re)
		return ;
	re->command_fail = 0;
	tmp_in = input;
	input_execv = parse_exev_input(tmp_in);
	split_execv = ft_split(input_execv, ' ');
	if (!split_execv || !split_execv[0])
	{
		free_split(split_execv);
		free(re);
		free(input_execv);
		return ;
	}
	if_need_sep = unstick_to_re_stick(tmp_in);
	split_in = ft_split(if_need_sep, ' ');
	if (!split_in || !split_in[0])
	{
		free_split(split_in);
		free_split(split_execv);
		free(re);
		free(input_execv);
		return ;
	}
	last_name = ft_strlonglen(split_in);
	path = find_command_path(split_in[0]);
	pid = fork();
	if (pid == -1)
	{
		free_split(split_in);
		free_split(split_execv);
		free(re);
		free(input_execv);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		heredoc_fd = open_available(&heredoc_tmpfile);
		if (heredoc_fd < 0)
		{
			perror("🔒 Erreur création fichier temporaire here-doc final");
			exit(EXIT_FAILURE);
		}
		for (int i = 1; i < last_name; i++)
		{
			if (strcmp(split_in[i], "<<") == 0)
			{
				fd = open_available(&tmpfilenames[heredoc_count]);
				if (fd < 0)
				{
					perror("🔒 Erreur création fichier here-doc");
					exit(EXIT_FAILURE);
				}
				delimiter = split_in[i + 1];
				ret = write_to_tmpfile(fd, delimiter, ee);
				close(fd);
				if (ret != 0)
				{
					perror("🔒 Erreur écriture here-doc");
					unlink(tmpfilenames[heredoc_count]);
					exit(EXIT_FAILURE);
				}
				fd = open(tmpfilenames[heredoc_count], O_RDONLY);
				if (fd < 0)
				{
					perror("🔒 Erreur ouverture fichier here-doc");
					unlink(tmpfilenames[heredoc_count]);
					exit(EXIT_FAILURE);
				}
				while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
				{
					write(heredoc_fd, buffer, bytes);
				}
				close(fd);
				unlink(tmpfilenames[heredoc_count]);
				heredoc_count++;
				i++;
			}
		}
		close(heredoc_fd);
		heredoc_fd = open(heredoc_tmpfile, O_RDONLY);
		if (heredoc_fd < 0)
		{
			perror("🔒 Erreur ouverture fichier here-doc final");
			exit(EXIT_FAILURE);
		}
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
		unlink(heredoc_tmpfile);
		for (int i = 1; i < last_name; i++)
		{
			if (strcmp(split_in[i], ">") == 0)
			{
				file = open(split_in[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
						0777);
				if (file == -1)
				{
					perror("🔒 Erreur ouverture fichier '>'");
					exit(EXIT_FAILURE);
				}
				dup2(file, STDOUT_FILENO);
				close(file);
				i++;
			}
			else if (strcmp(split_in[i], ">>") == 0)
			{
				file = open(split_in[i + 1], O_WRONLY | O_CREAT | O_APPEND,
						0777);
				if (file == -1)
				{
					perror("🔒 Erreur ouverture fichier '>>'");
					exit(EXIT_FAILURE);
				}
				dup2(file, STDOUT_FILENO);
				close(file);
				i++;
			}
		}
		execv(path, split_execv);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (!g_status)
			{
				ee->signal = WEXITSTATUS(status);
				if (ee->signal != 0 && ee->signal != 1)
					ee->signal = 128 + ee->signal;
			}
		}
	}
	if (!path)
	{
		ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", split_in[0]);
		ee->signal = 127;
		ee->confirmed_command = 0;
	}
	else
		ee->confirmed_command = 1;
	signal(SIGINT, handle_sigint);
	free_split(split_execv);
	free_split(split_in);
	free(input_execv);
	free(if_need_sep);
	free(path);
	free(re);
}*/
