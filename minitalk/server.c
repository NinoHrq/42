/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:30:34 by nharraqi          #+#    #+#             */
/*   Updated: 2024/10/07 19:40:58 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig)
{
	static char			c = 0;
	static unsigned int	bit_pos = 0;

	if (sig == SIGUSR1)
		c = (c << 1);
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	bit_pos++;
	if (bit_pos == 8)
	{
		ft_printf("%c", c);
		bit_pos = 0;
		c = 0;
	}
}

int	main(void)
{
	int	pid;

	ft_printf("Welcome\n");
	pid = getpid();
	ft_printf("Server's PID : %d\n", pid);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
