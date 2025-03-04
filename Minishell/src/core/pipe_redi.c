/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:29:00 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 17:39:53 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_child_process(t_pipeline *p, t_ee *ee)
{
	if (p->prev_fd != -1)
		dup2(p->prev_fd, STDIN_FILENO);
	if (p->heredoc_fd != -1)
		dup2(p->heredoc_fd, STDIN_FILENO);
	else if (p->input_fd != -1)
		dup2(p->input_fd, STDIN_FILENO);
	if (p->commands[p->i + 1])
		dup2(p->pipe_fd[1], STDOUT_FILENO);
	if (p->output_fd != -1)
		dup2(p->output_fd, STDOUT_FILENO);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	cumulate_token(p->final_command, ee);
}

void	path_and_free_piperedi(t_pipeline *p, char *input, t_ee *ee)
{
	if (p->prev_fd != -1)
		close(p->prev_fd);
	while (wait(NULL) > 0)
		;
	if (p->commands)
		free_split(p->commands);
	path_confirm(input);
	path_checker(input, ee);
	if (p)
	{
		free(p);
		p = NULL;
	}
}

int	execute_child(t_pipeline *p, t_ee *ee)
{
	handle_child_process(p, ee);
	exit(EXIT_FAILURE);
}

void	main_core(t_pipeline *p, char *input, t_ee *ee)
{
	p->final_command = handle_redi_with_pipe(p->commands[p->i], ee, p);
	if (!p->final_command)
	{
		handle_error_piperedi("🔒 Erreur lors du traitement des redirections", p,
			input);
		return ;
	}
	p->final_command = parse_final_command(p->final_command);
	if (pipe(p->pipe_fd) == -1)
	{
		handle_error_piperedi("pipe", p, input);
		return ;
	}
	p->pid = fork();
	if (p->pid == -1)
	{
		handle_error_piperedi("fork", p, input);
		return ;
	}
	if (p->pid == 0)
		execute_child(p, ee);
	close_fds_and_update(p);
	free(p->final_command);
}

int	execute_pipeline_heredoc(char *input, t_ee *ee)
{
	t_pipeline	*p;

	p = malloc(sizeof(t_pipeline));
	if (!p)
		return (handle_error("malloc", p, input));
	p->prev_fd = -1;
	p->i = 0;
	input = parse_input_pipeline(input);
	p->commands = ft_split(input, '|');
	if (!p->commands)
		return (handle_error("Failed to split commands", p, input));
	while (p->commands[p->i])
	{
		main_core(p, input, ee);
		p->i++;
	}
	path_and_free_piperedi(p, input, ee);
	return (0);
}

/*int execute_pipeline_heredoc(char *input, t_ee *ee)
{
	char **commands;
	char **check_path;
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;
	int i = 0;

	input = parse_input_pipeline(input);
	commands = ft_split(input, '|');
	while (commands[i])
	{
		int heredoc_fd, input_fd, output_fd;
		char *final_command = handle_redi_with_pipe(commands[i], ee,
				&heredoc_fd, &input_fd, &output_fd);
		if (!final_command)
		{
			perror("🔒 Erreur lors du traitement des redirections");
			free_split(commands);
			free(input); // Libération de l'input modifié
			return (-1);
		}
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			free(final_command);
			free_split(commands);
			free(input); // Libération de l'input modifié
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(final_command);
			free_split(commands);
			free(input); // Libération de l'input modifié
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (heredoc_fd != -1)
			{
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
			else if (input_fd != -1)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (commands[i + 1])
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (output_fd != -1)
			{
				dup2(output_fd, STDOUT_FILENO);
				close(output_fd);
			}
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			interprete_commande(final_command, ee);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipe_fd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = pipe_fd[0];
			if (heredoc_fd != -1)
				close(heredoc_fd);
			if (input_fd != -1)
				close(input_fd);
			if (output_fd != -1)
				close(output_fd);
		}
		free(final_command);
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	while (wait(NULL) > 0);
	free_split(commands);

	check_path = ft_split(input, ' ');
	char *path = find_command_path(check_path[0]);
	if (!path)
	{
		ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", check_path[0]);
	}
	free_split(check_path);
	free(path);
	check_path = ft_split(input, ' ');
	path = find_command_path(check_path[calcul_check_path(check_path)]);
	if (!path)
	{
		ee->signal = 127;
		ee->check_and_validity = 1;
		ee->confirmed_command = 0;
	}
	else
	{
		ee->signal = 0;
		ee->check_and_validity = 0;
		ee->confirmed_command = 1;
	}
	free_split(check_path);
	free(path);
	free(input);
	return (0);
}*/
