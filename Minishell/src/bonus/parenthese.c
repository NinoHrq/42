/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthese.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:24:51 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:24:52 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_parentheses_execution(t_parenthese *par, t_ee *ee)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("Erreur fork()");
		free(par->command_before_or);
		free(par->command_after_or);
		return ;
	}
	if (pid == 0)
	{
		its_just_a_parenthese(par->command_after_or, ee);
		exit(ee->signal);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ee->signal = WEXITSTATUS(status);
	}
}

void	process_or_case(char *input, t_ee *ee)
{
	t_parenthese	*par;
	bool			has_parentheses;

	par = malloc(sizeof(t_parenthese));
	if (!par)
		return ;
	par->command_before_or = copy_before_or(input);
	par->command_after_or = copy_after_or(input);
	has_parentheses = (find_parenthesis(par->command_after_or) == 1);
	cumulate_token(par->command_before_or, ee);
	if (ee->signal != 0)
	{
		if (has_parentheses)
			handle_parentheses_execution(par, ee);
		else
			cumulate_token(par->command_after_or, ee);
	}
	free(par->command_before_or);
	free(par->command_after_or);
	free(par);
}

void	execute_cleaned_input(char *clean_input, t_ee *ee)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("Erreur fork()");
		free(clean_input);
		return ;
	}
	if (pid == 0)
	{
		cumulate_token(clean_input, ee);
		exit(ee->signal);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ee->signal = WEXITSTATUS(status);
		if (ee->signal == 127)
			ee->check_and_validity = 1;
	}
	free(clean_input);
}

void	its_just_a_parenthese(char *input, t_ee *ee)
{
	char	*clean_input;

	if (do_you_find_or_what(input) == 1)
	{
		process_or_case(input, ee);
		return ;
	}
	clean_input = remove_parentheses(input);
	if (!clean_input)
		return ;
	execute_cleaned_input(clean_input, ee);
}

/*void	its_just_a_parenthese(char *input, t_ee *ee)
{
	char *clean_input;
	char *command_before_or;
	char *command_after_or;
	bool has_parentheses = false;

	if (do_you_find_or_what(input) == 1)
	{
		command_before_or = copy_before_or(input);
		command_after_or = copy_after_or(input);
		has_parentheses = (find_parenthesis(command_after_or) == 1);
		cumulate_token(command_before_or, ee);
		if (ee->signal != 0)
		{
			if (has_parentheses)
			{
				pid_t pid = fork();
				if (pid == -1)
				{
					perror("Erreur fork()");
					free(command_before_or);
					free(command_after_or);
					return ;
				}
				if (pid == 0)
				{
					its_just_a_parenthese(command_after_or, ee);
					exit(ee->signal);
				}
				else
				{
					int status;
					waitpid(pid, &status, 0);
					if (WIFEXITED(status))
						ee->signal = WEXITSTATUS(status);
				}
			}
			else
				cumulate_token(command_after_or, ee);
		}
		free(command_before_or);
		free(command_after_or);
		return ;
	}
	clean_input = remove_parentheses(input);
	if (!clean_input)
		return ;
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("Erreur fork()");
		free(clean_input);
		return ;
	}
	if (pid == 0)
	{
		cumulate_token(clean_input, ee);
		exit(ee->signal);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ee->signal = WEXITSTATUS(status);
		if (ee->signal == 127)
			ee->check_and_validity = 1;
	}
	free(clean_input);
}*/
