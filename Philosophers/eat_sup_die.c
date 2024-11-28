/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sup_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:18:32 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/28 19:32:24 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spe_case(t_param *param, t_philo *philo, char c)
{
	while (1)
	{
		pthread_mutex_lock(&param->protect_dead);
		if (param->p_dead != 0)
		{
			pthread_mutex_unlock(&param->protect_dead);
			return ;
		}
		pthread_mutex_unlock(&param->protect_dead);
		if (c == 'e')
			eat_sup_die(param, philo);
		else if (c == 's')
			sleep_sup_die(param, philo);
	}
}

void	eat_sup_die(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	if (philo->id % 2 != 0)
		usleep(param->time_to_eat * 1000);
	if (philo->id % 2 == 0)
		take_forks_even(param, philo);
	else
		take_forks_odd(param, philo);
	after_forks_spe_eat(param, philo);
}

void	after_forks_spe_eat(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	if (philo->id % 2 == 0)
	{
		for_eat(philo, param, time);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		usleep(param->time_to_die * 1e3);
	}
	else if (philo->id % 2 != 0)
	{
		for_eat(philo, param, time);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		usleep(param->time_to_die * 1e3);
	}
	pthread_mutex_lock(&param->protect_dead);
	if (param->p_dead == 0)
		printd_dead(param, philo, time);
	param->p_dead = 1;
	pthread_mutex_unlock(&param->protect_dead);
}

void	printd_dead(t_param *param, t_philo *philo, long time)
{
	pthread_mutex_lock(&param->protect_printf);
	time = get_current_time() - param->start_simulation;
	printf("%ld %d died\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
}

void	sleep_sup_die(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	if (philo->id % 2 != 0)
		usleep(param->time_to_eat * 1000);
	if (philo->id % 2 == 0)
		take_forks_even(param, philo);
	else
		take_forks_odd(param, philo);
	after_forks_spe_sleep(param, philo);
}

void	after_forks_spe_sleep(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	if (philo->id % 2 == 0)
	{
		for_eat(philo, param, time);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		usleep(param->time_to_eat * 1000);
	}
	else if (philo->id % 2 != 0)
	{
		for_eat(philo, param, time);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		usleep(param->time_to_eat * 1e3);
	}
	usleep((param->time_to_die - param->time_to_eat) * 1e3);
	pthread_mutex_lock(&param->protect_dead);
	if (param->p_dead == 0)
		printd_dead(param, philo, time);
	param->p_dead = 1;
	pthread_mutex_unlock(&param->protect_dead);
}
