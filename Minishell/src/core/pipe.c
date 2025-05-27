/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:28:52 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/07 21:12:17 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	nm_pid_equal_to_zero(int pipe_fd[2], t_pipe *piipe, t_ee *ee)
{
	if (piipe->prev_fd != -1)
	{
		dup2(piipe->prev_fd, STDIN_FILENO);
		close(piipe->prev_fd);
	}
	if (piipe->commands[piipe->i + 1])
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	cumulate_token(piipe->commands[piipe->i], ee);
	return ;
}

void	nm_pid_not_equal_to_zero(int pipe_fd[2], t_pipe *piipe)
{
	close(pipe_fd[1]);
	if (piipe->prev_fd != -1)
	{
		close(piipe->prev_fd);
	}
	piipe->prev_fd = pipe_fd[0];
	return ;
}

void	do_what_pipe_need(int pipe_fd[2], t_pipe *piipe, t_ee *ee)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	piipe->pid = fork();
	if (piipe->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (piipe->pid == 0)
	{
		nm_pid_equal_to_zero(pipe_fd, piipe, ee);
		exit(EXIT_FAILURE);
	}
	else
		nm_pid_not_equal_to_zero(pipe_fd, piipe);
	piipe->i++;
}

int	execute_pipeline(char *input, t_ee *ee)
{
	int		pipe_fd[2];
	t_pipe	*piipe;

	piipe = malloc(sizeof(t_pipe));
	if (!piipe)
		return (-1);
	init_pipe_struct(piipe);
	input = parse_input_pipeline(input);
	piipe->commands = ft_splittt(input, '|');
	while (piipe->commands[piipe->i])
		do_what_pipe_need(pipe_fd, piipe, ee);
	if (piipe->prev_fd != -1)
		close(piipe->prev_fd);
	while (wait(NULL) > 0)
		;
	free_split(piipe->commands);
	path_confirm(input);
	path_checker(input, ee);
	free(piipe);
	return (0);
}

/*int execute_pipeline(char *input, t_ee *ee)
{
	char **commands;
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;
	int i = 0;

	input = parse_input_pipeline(input);
	commands = ft_split(input, '|');
	if (!commands) {
		perror("ft_split");
		free(input);
		return (-1);
	}
	while (commands[i])
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			free_split(commands);
			free(input);
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free_split(commands);
			free(input);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (commands[i + 1])
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
			}
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			interprete_commande(commands[i], ee);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipe_fd[1]);
			if (prev_fd != -1)
			{
				close(prev_fd);
			}
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	while (wait(NULL) > 0);
	free_split(commands);
	char **check_path = ft_split(input, ' ');
	if (check_path)
	{
		char *path = find_command_path(check_path[0]);
		if (!path)
			ft_printf("🍁_(`へ´*)_🍁: %s: command not found\n", check_path[0]);

		free_split(check_path);
		free(path);
	}
	check_path = ft_split(input, ' ');
	if (check_path)
	{
		char *path = find_command_path(check_path[calcul_check_path(check_path)]);
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
	}
	free(input);
	return (0);
}*/
