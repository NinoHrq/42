/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:31:52 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 20:17:48 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		error_quit("The input is not a correct digit");
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			error_quit("Give me only positive values dummy!");
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > (LONG_MAX / 10) || (number == (LONG_MAX / 10) && (str[i]
				- '0') > (LONG_MAX % 10)))
		error_quit("Number is too large");
	return (number);
}

void	parse_input(t_param **table, char **av)
{
	int	i;

	(*table)->philo_nbr = ft_atol(av[1]);
	(*table)->time_to_die = ft_atol(av[2]);
	(*table)->time_to_eat = ft_atol(av[3]);
	(*table)->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		(*table)->nbr_limit_meals = ft_atol(av[5]);
	else
		(*table)->nbr_limit_meals = -1;
	pthread_mutex_init(&(*table)->protect_printf, NULL);
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * (*table)->philo_nbr);
	if (!(*table)->forks)
		error_quit("Malloc failed");
	i = -1;
	while (++i < (*table)->philo_nbr)
		pthread_mutex_init(&(*table)->forks[i], NULL);
	pthread_mutex_init(&(*table)->protect_forks, NULL);
	(*table)->start_simulation = get_current_time();
}

void parse_philo(t_param *param, t_philo *philo)
{
	int i;
	
	i = -1;
	while(++i < param->philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].meals_counter = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].left_fork = &param->forks[i];
		philo[i].right_fork = &param->forks[i + 1 ] % param->philo_nbr;
		 
	}
}
