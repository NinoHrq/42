/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:25 by nharraqi          #+#    #+#             */
/*   Updated: 2024/10/07 19:37:08 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*str;
	int		i;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server_pid] [message]\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
	{
		send_char(server_pid, str[i]);
		i++;
	}
	send_char(server_pid, '\n');
	return (0);
}
