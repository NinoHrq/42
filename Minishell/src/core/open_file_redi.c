/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <tmilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:36:20 by tmilin            #+#    #+#             */
/*   Updated: 2025/03/03 17:36:35 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	does_exit_final_filename(t_open openn)
{
	if (!openn.final_filename)
	{
		free(openn.idxstr);
		return (1);
	}
	return (0);
}

int	open_available(char **tmpfilename)
{
	t_open	openn;

	openn.tmp_dir = "/tmp/tmp_for_heredoc_";
	openn.i = 0;
	while (openn.i < 65535)
	{
		openn.idxstr = ft_itoa(openn.i);
		openn.final_filename = (char *)malloc(ft_strlen(openn.tmp_dir)
				+ ft_strlen(openn.idxstr) + 1);
		if (does_exit_final_filename(openn))
			return (-1);
		strcpy(openn.final_filename, openn.tmp_dir);
		ft_strcat(openn.final_filename, openn.idxstr);
		free(openn.idxstr);
		openn.fd = open(openn.final_filename, O_WRONLY | O_CREAT | O_EXCL,
				0644);
		if (openn.fd >= 0)
		{
			*tmpfilename = openn.final_filename;
			return (openn.fd);
		}
		free(openn.final_filename);
		openn.i++;
	}
	return (-1);
}

char	*get_env_valueee(char *key, t_ee *ee)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = strlen(key);
	while (ee->envp[i])
	{
		if (strncmp(ee->envp[i], key, key_len) == 0
			&& ee->envp[i][key_len] == '=')
			return (ft_strdup(ee->envp[i] + key_len + 1));
		i++;
	}
	return (ft_strdup(""));
}

int	write_to_tmpfile(int fd, char *limit, t_ee *ee)
{
	char	*input;
	int		i;

	input = NULL;
	signal(SIGINT, handle_herdoc_sigint);
	while (1)
	{
		input = readline("🗒️🖊️  ");
		if (!input || ft_strcmp(input, limit) == 0)
		{
			free(input);
			break ;
		}
		i = 0;
		while (input[i])
		{
			if (input[i] == '$')
				set_value_dollars(&input, ee);
			i++;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	return (0);
}
