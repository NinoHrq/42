/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:05:54 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 20:06:56 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf(RED "Wrong numbers of arguments\n" RST);
		return (1);
	}
	else if (av[1][0] == '0')
	{
		printf(RED "Wrong number of philo\n" RST);
		return (1);
	}
	else if (av[2][0] == '0')
	{
		printf(RED "Wrong number of die_time\n" RST);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_param *param;
	t_philo *philo;

	if (check_param(ac, av))
		return (0);
	param = malloc(sizeof(t_param));
	parse_input(&param, av);
	philo = malloc(sizeof(t_philo) * param->philo_nbr);
	
}