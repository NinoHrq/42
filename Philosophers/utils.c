/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:30:57 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 20:09:47 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_quit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

long	get_current_time(void)
{
	struct timeval *tv;

	gettimeofday(&tv, NULL);
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}