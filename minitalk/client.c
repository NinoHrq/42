/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:25 by nharraqi          #+#    #+#             */
/*   Updated: 2024/10/18 18:30:34 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*void	send_onebit(int pid, char bit)
{
	if (bit == '0')
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(300);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> (7 - i)) & 1)
			send_onebit(pid, '1');
		else
			send_onebit(pid, '0');
		//usleep(500);
		i++;
	}
}

void	send_all(int pid, const char *message)
{
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid,'\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server_pid] [message]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	send_all(pid, argv[2]);
	return (0);
}*/

void	send_char(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		bit--;
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
	return (0);
}
