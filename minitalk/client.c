/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:25 by nharraqi          #+#    #+#             */
/*   Updated: 2024/10/22 17:12:03 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;
	char	*message;

	if (ac != 3)
	{
		ft_printf("\n\tUsage : ./client PID ""message""\n\n");
		return (0);
	}
	pid = ft_atoi(av[1]);
	if (pid != ft_atoi(av[1]))
		return (0);
	message = av[2];
	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\n');
	return (0);
}
