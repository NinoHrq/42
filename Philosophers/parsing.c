/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:31:52 by nharraqi          #+#    #+#             */
/*   Updated: 2025/03/07 18:49:40 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str, t_param *param)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		error_quit_param("The input is not a correct digit", param);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			error_quit_param("Give me only positive values dummy!", param);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX || number < 0)
		error_quit_param("Number is too large", param);
	return (number);
}

void	parse_input(t_param **param, char **av)
{
	int	i;

	(*param)->philo_nbr = ft_atol(av[1], (*param));
	(*param)->time_to_die = ft_atol(av[2], (*param));
	(*param)->time_to_eat = ft_atol(av[3], (*param));
	(*param)->time_to_sleep = ft_atol(av[4], (*param));
	if (av[5])
		(*param)->nbr_limit_meals = ft_atol(av[5], (*param));
	else
		(*param)->nbr_limit_meals = -1;
	pthread_mutex_init(&(*param)->protect_printf, NULL);
	(*param)->forks = malloc(sizeof(pthread_mutex_t) * (*param)->philo_nbr);
	if (!(*param)->forks)
		error_quit_param("Malloc failed", (*param));
	i = -1;
	while (++i < (*param)->philo_nbr)
		pthread_mutex_init(&(*param)->forks[i], NULL);
	pthread_mutex_init(&(*param)->protect_forks, NULL);
	pthread_mutex_init(&(*param)->protect_dead, NULL);
	(*param)->p_dead = 0;
	(*param)->start_simulation = get_current_time();
}

int	parse_philo(t_param *param, t_philo *philo)
{
	int	i;
	int	res;

	i = 0;
	while (i < param->philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].meals_counter = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].left_fork = &param->forks[i];
		philo[i].right_fork = &param->forks[(i + 1) % param->philo_nbr];
		philo[i].param = param;
		res = pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		if (res != 0)
		{
			printf("Error creating thread philo");
			return (1);
		}
		i++;
	}
	return (0);
}
