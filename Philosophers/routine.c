/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:31:27 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/28 19:53:21 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	only_one(t_param *param, t_philo *philo, long time)
{
	printf("%ld %d has taken a fork\n", time, philo->id);
	usleep(param->time_to_die * 1e3);
	time = get_current_time() - param->start_simulation;
	printf("%ld %d died\n", time, philo->id);
}

void	*routine(void *arg)
{
	t_param	*param;
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	param = philo->param;
	time = get_current_time() - param->start_simulation;
	if (param->philo_nbr == 1)
	{
		only_one(param, philo, time);
		return (NULL);
	}
	if (param->time_to_eat >= param->time_to_die)
		spe_case(param, philo, 'e');
	if ((param->time_to_sleep >= param->time_to_die) || ((param->time_to_eat
				- param->time_to_sleep) + param->time_to_eat
			+ param->time_to_sleep >= param->time_to_die) || (param->philo_nbr
			% 2 != 0 && (param->time_to_eat * 3 >= param->time_to_die)))
		spe_case(param, philo, 's');
	if (param->nbr_limit_meals == -1)
		eat_infinite(param, philo);
	else if (!(param->nbr_limit_meals == -1))
		eat_your_meals(param, philo);
	return (NULL);
}
void	eat_infinite(t_param *param, t_philo *philo)
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
		dinner(param, philo);
	}
}

void	eat_your_meals(t_param *param, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < param->nbr_limit_meals)
	{
		pthread_mutex_lock(&param->protect_dead);
		if (param->p_dead != 0)
		{
			pthread_mutex_unlock(&param->protect_dead);
			return ;
		}
		pthread_mutex_unlock(&param->protect_dead);
		dinner(param, philo);
		i++;
	}
}

void	dinner(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	pthread_mutex_lock(&param->protect_dead);
	if (param->p_dead == 0 && get_current_time()
		- philo->last_meal_time >= param->time_to_die)
	{
		pthread_mutex_lock(&param->protect_printf);
		printf("%ld %d died\n", time, philo->id);
		pthread_mutex_unlock(&param->protect_printf);
		param->p_dead = 1;
	}
	pthread_mutex_unlock(&param->protect_dead);
	if (philo->id % 2 != 0)
		usleep(param->time_to_eat * 1000);
	if (philo->id % 2 == 0)
		take_forks_even(param, philo);
	else
		take_forks_odd(param, philo);
	after_forks(param, philo);
}
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

void	after_forks(t_param *param, t_philo *philo)
{
	long	time;

	time = get_current_time() - param->start_simulation;
	if (philo->id % 2 == 0)
	{
		for_eat(philo, param, time);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		usleep(param->time_to_eat * 1e3);
	}
	else if (philo->id % 2 != 0)
	{
		for_eat(philo, param, time);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		usleep(param->time_to_eat * 1e3);
	}
	for_sleep(philo, param, time);
	usleep(param->time_to_sleep * 1e3);
	for_think(philo, param, time);
	if (param->time_to_eat > param->time_to_sleep)
		usleep((param->time_to_eat - param->time_to_sleep) * 1000);
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