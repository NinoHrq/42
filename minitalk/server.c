/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:34 by nharraqi          #+#    #+#             */
/*   Updated: 2024/10/14 16:38:58 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*static char	buffer[SIZE + 1];

void	buffer_printnclear(void)
{
	int	i;

	i = 0;
	ft_printf("\n%s", buffer);
	buffer[0] = '\0';
}

void	fill_buff(char c)
{
	static	int	i = 0;

	if (i < SIZE - 1)
	{
		buffer[i] = c;
		i++;
		buffer[i] = '\0';
	}
	if (i >= SIZE - 1)
	{
		buffer_printnclear();
		i = 0;
	}
}

void	handle_signal(int sig)
{
	static char	c = 0;
	static int	bit_pos = 0;

	if (sig == SIGUSR1)
		c = (c << 1);
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	bit_pos++;
	if (bit_pos == 8)
	{
		if (c == '\0')
		{
			buffer_printnclear();
		}
		else
		{
			fill_buff(c);
		}
		bit_pos = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	int			pid;
	static int	count_bit = 0;
	static char	c = 0;

	(void)av;
	if (ac !=1)
	{
		ft_printf("\n Usage ; ./server\n\n");
		return (0);
	}
	ft_printf("Welcome\n");
	pid = getpid();
	ft_printf("Server's PID : %d\n", pid);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}*/
void	handle_signal(int bit)
{
	static int	count_bit = 0;
	static char	c = 0;
	
	if (bit == SIGUSR1)
		c = c << 1;
	else if (bit == SIGUSR2)
		c = (c << 1) | 1;
	count_bit++;
	if (count_bit == 8)
	{
		ft_printf("%c", c);
		count_bit = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	int pid;

	(void)av;
	if (ac != 1)
	{
		ft_printf("\n    Usage : ./server\n\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\n    PID : %d\n\n", pid);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
	{
		pause();
	}
	return (0);
}