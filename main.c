/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:05:54 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/29 14:39:19 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Wrong numbers of arguments\n");
		return (1);
	}
	else if (av[1][0] == '0')
	{
		printf("Wrong number of philo\n");
		return (1);
	}
	else if (av[2][0] == '0')
	{
		printf("Wrong number of die_time\n");
		return (1);
	}
	return (0);
}

void	free_all(t_param *param, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < param->philo_nbr)
		pthread_mutex_destroy(&param->forks[i]);
	pthread_mutex_destroy(&param->protect_dead);
	pthread_mutex_destroy(&param->protect_forks);
	pthread_mutex_destroy(&param->protect_printf);
	free(param->forks);
	free(param);
	free(philo);
}

int	main(int ac, char **av)
{
	int			i;
	t_param		*param;
	t_philo		*philo;

	i = -1;
	if (check_param(ac, av))
		return (0);
	param = malloc(sizeof(t_param));
	parse_input(&param, av);
	philo = malloc(sizeof(t_philo) * param->philo_nbr);
	parse_philo(param, philo);
	while (++i < param->philo_nbr)
		pthread_join(philo[i].thread, NULL);
	free_all(param, philo);
	return (0);
}
