/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:31:54 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/29 14:35:02 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_even(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	if (param->p_dead == 0)
		printf("%ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	time = get_current_time() - param->start_simulation;
	if (param->p_dead == 0)
		printf("%ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
}

void	take_forks_odd(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	if (param->p_dead == 0)
		printf("%ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	time = get_current_time() - param->start_simulation;
	if (param->p_dead == 0)
		printf("%ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
}

void	for_eat(t_philo *philo, t_param *param, long time)
{
	time = get_current_time() - param->start_simulation;
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	if (param->p_dead == 0)
		printf("%ld %d is eating\n", time, philo->id);
	philo->meals_counter++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
}

void	for_sleep(t_philo *philo, t_param *param, long time)
{
	time = get_current_time() - param->start_simulation;
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	if (param->p_dead == 0)
		printf("%ld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
}

void	for_think(t_philo *philo, t_param *param, long time)
{
	time = get_current_time() - param->start_simulation;
	pthread_mutex_lock(&param->protect_dead);
	pthread_mutex_lock(&param->protect_printf);
	if (param->p_dead == 0)
		printf("%ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&param->protect_printf);
	pthread_mutex_unlock(&param->protect_dead);
}
