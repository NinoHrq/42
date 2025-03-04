/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:34:43 by tmilin            #+#    #+#             */
/*   Updated: 2025/02/27 19:34:44 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strcat_export(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	int		j;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i++] = s2[j++];
	}
	result[i] = '\0';
	return (result);
}

char	*parse_home(char *home)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (home[i] && home[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (ft_strlen(home) - i + 1));
	j = 0;
	while (home[i])
	{
		tmp[j++] = home[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	check_if_home_is_set(t_ee *ee, char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = parse_home(ee->copy_home);
	while (args[i])
	{
		if (ee->copy_home && ft_strcmp(args[i], ee->copy_home) == 0)
		{
			ee->block_home = 0;
			break ;
		}
		i++;
	}
	free(tmp);
}

void	check_if_path_is_not_modified(t_ee *ee, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == 'P' && args[i][1] == 'A' && args[i][2] == 'T'
			&& args[i][3] == 'H' && args[i][4] == '=')
			break ;
		i++;
	}
	if (args[i])
	{
		if ((ft_strcmp(args[i], ee->save_initial_path) != 0)
			|| (ft_strcmp(args[i], "PATH=/bin:/usr/bin") != 0))
			ee->lock_path = 1;
	}
	return ;
}

void	check_if_home_is_not_modified(t_ee *ee, char **args)
{
	int	i;

	i = 0;
	(void)ee;
	while (args[i])
	{
		if (args[i][0] == 'H' && args[i][1] == 'O' && args[i][2] == 'M'
			&& args[i][3] == 'E' && args[i][4] == '=')
			break ;
		i++;
	}
	if (args[i])
	{
		if (ft_strcmp(args[i], ee->copy_home) != 0)
			ee->block_home = 1;
	}
	return ;
}
