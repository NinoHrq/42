/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:27:56 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/08 11:35:20 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_pid_is_equal_to_zero(char *path, char **args, t_ee *ee,
		char *command)
{
	int	i;

	i = 0;
	if (command[i] == '.' && command[i + 1] == '/')
		error_access(command);
	if (ee->reset_sigint == 1)
		signal(SIGINT, handle_sigint);
	ee->reset_sigint = 0;
	printf_expand_var(args[0], ee);
	if (execve(path, args, ee->envp) == -1)
	{
		perror("execve");
		if (access(path, F_OK) == -1)
			exit(127);
		if (errno == EACCES)
			exit(126);
		if (errno == ENOEXEC)
			exit(0);
		exit(EXIT_FAILURE);
	}
}

void	if_pid_is_sup_to_zero(t_ee *ee, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (!g_status)
			ee->signal = WEXITSTATUS(status);
		else
			ee->signal = 0;
	}
	else if (WIFSIGNALED(status))
		ee->signal = WTERMSIG(status) + 128;
	if (ee->signal == 127 || ee->signal == 126 || ee->signal == 1)
	{
		if (ee->command_with_and)
			ee->check_and_validity = 1;
		ee->confirmed_command = 0;
	}
	if (ee->reset_sigint == 1)
		signal(SIGINT, handle_sigint);
	ee->reset_sigint = 0;
}

int	printf_expand_var(char *input, t_ee *ee)
{
	t_varex	v;

	init_varex(&v);
	while (ee->envp[v.i])
	{
		v.j = 0;
		while (ee->envp[v.i][v.j] && ee->envp[v.i][v.j] != '=')
			v.j++;
		if (ee->envp[v.i][v.j] == '=')
		{
			v.j++;
			v.k = 0;
			while (ee->envp[v.i][v.j])
				v.tmp[v.k++] = ee->envp[v.i][v.j++];
			v.tmp[v.k] = '\0';
			if (strcmp(v.tmp, input) == 0)
			{
				printf("💲%s\n", input);
				return (1);
			}
		}
		v.i++;
	}
	return (0);
}

void	bilbon_the_saquet(char **args, char *command, t_ee *ee)
{
	char	*path;
	pid_t	pid;

	path = find_command_path(args[0]);
	if (!path)
	{
		if_path_is_incorrect(args, ee);
		return ;
	}
	else
		ee->confirmed_command = 1;
	pid = fork();
	if (pid == 0)
		if_pid_is_equal_to_zero(path, args, ee, command);
	else if (pid > 0)
		if_pid_is_sup_to_zero(ee, pid);
	else
		perror("fork");
	free(path);
}

void	execute_external_command(char *command, t_ee *ee)
{
	char	**args;
	char	**tmp;

	if (command[0] == '\0')
		return ;
	check_signal(command, ee);
	args = ft_splittt(command, ' ');
	remoov_quote__(args);
	tmp = parse_dollarsss(args, ee);
	remoov_single__quote__(tmp);
	free_split(args);
	args = tmp;
	if (args[0])
	{
		bilbon_the_saquet(args, command, ee);
	}
	else
		ee->confirmed_command = 1;
	free_split(args);
}
