/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:16:54 by nharraqi          #+#    #+#             */
/*   Updated: 2025/02/04 15:16:54 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_input_cd(char *input);
void	ft_cd(char *input, t_ee *ee);
void	handle_home_directory(t_ee *ee, t_cd *cd, int result);
int		change_directory(t_ee *ee, t_cd *cd, int result);
void	free_cd_struct(t_cd *cd);

char	*parse_input_cd(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == ';' && i > 0 && input[i - 1] != ' ')
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	return (input);
}

void	ft_cd(char *input, t_ee *ee)
{
	t_cd	*cd;
	int		result;

	cd = malloc(sizeof(t_cd));
	result = 0;
	input = parse_input_cd(input);
	cd->args = ft_split(input, ' ');
	ee->copy_oldpwd = getcwd(NULL, 0);
	ee->change_confirmed = 1;
	if (cd->args[1] == NULL || ft_strcmp(cd->args[0], "~") == 0)
		handle_home_directory(ee, cd, result);
	else
	{
		change_directory(ee, cd, result);
	}
	if (result != 0)
	{
		perror("🍂_(´~`)_🍂: cd");
		free_split(cd->args);
		free(cd);
		return ;
	}
	free_cd_struct(cd);
}

void	handle_home_directory(t_ee *ee, t_cd *cd, int result)
{
	ee->change_confirmed = 1;
	cd->home = getenv("HOME");
	if (cd->home == NULL)
	{
		printf("🍂_(´~`)_🍂: HOME not set\n");
		free_cd_struct(cd);
		return ;
	}
	else
	{
		result = chdir(cd->home);
		if (ee->copy_pwd)
			free(ee->copy_pwd);
		ee->copy_pwd = getcwd(NULL, 0);
		check_variable_pwd(ee);
	}
}

int	change_directory(t_ee *ee, t_cd *cd, int result)
{
	if (ee->copy_pwd)
		free(ee->copy_pwd);
	if (ee->copy_oldpwd)
		free(ee->copy_oldpwd);
	ee->change_confirmed = 1;
	ee->copy_oldpwd = getcwd(NULL, 0);
	result = chdir(cd->args[1]);
	ee->copy_pwd = getcwd(NULL, 0);
	check_variable_pwd(ee);
	return (result);
}

void	free_cd_struct(t_cd *cd)
{
	free_split(cd->args);
	free(cd);
}
