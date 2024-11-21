/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:55:25 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 01:23:18 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
    int philo_nbr;
    
    philo_nbr = philo->table->philo_nbr;
    philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
    philo->second_fork = &forks[philo_position];
    if(philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_position];
        philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
    }
    
    
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while(++i < table->philo_nbr)
    {
        philo = table->philos + 1;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;

        assignforks(philo, table->forks, i);
    }
}

void data_init(t_table *table)
{
    int i;
    
    i = -1;
    table->end_simulation = false;
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
    while (++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}