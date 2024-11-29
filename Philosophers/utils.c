/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:30:57 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/29 14:42:47 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_quit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	printd_dead(t_param *param, t_philo *philo, long time)
{
	pthread_mutex_lock(&param->protect_printf);
	time = get_current_time() - param->start_simulation;
	printf("%ld %d died\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
}

void	only_one(t_param *param, t_philo *philo, long time)
{
	printf("%ld %d has taken a fork\n", time, philo->id);
	usleep(param->time_to_die * 1e3);
	time = get_current_time() - param->start_simulation;
	printf("%ld %d died\n", time, philo->id);
}