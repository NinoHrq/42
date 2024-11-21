/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:31:52 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 21:04:41 by nharraqi         ###   ########.fr       */
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
	if ((str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z'))
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
	if (number > (LONG_MAX / 10) || (number == (LONG_MAX / 10) && (str[i] - '0') 
        > (LONG_MAX % 10)))
    error_quit("Number is too large");
    return (number);
}

void parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3;
    table->time_to_eat = ft_atol(av[3]) * 1e3;
    table->time_to_sleep = ft_atol(av[4]) * 1e3;
    if (table->time_to_die < 6e4
        ||table->time_to_eat < 6e4
        ||table->time_to_sleep < 6e4)
        error_quit("Use times major than 60 ms");
    if(av[5])
        table->nbr_limit_meals = ft_atol(av[5]);
    else
        table->nbr_limit_meals = -1;  
}