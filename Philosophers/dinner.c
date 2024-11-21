/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:39:30 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 00:47:07 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void think(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}

static void eat(t_philo *philo)
{
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    safe_mutex_handle(&philo->philo_mutex, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    philo->meals_counter++;
    safe_mutex_handle(&philo->philo_mutex, UNLOCK);
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->nbr_limit_meals > 0
        && philo->meals_counter == philo->table->nbr_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}
void *dinner_simu(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_for_all_threads(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal_time,
        gettime(MILLISECOND));
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
    
    while(!simu_finished(philo->table))
    {
        if(philo->full)
            break;
        eat(philo);
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        think(philo);
    }
    return (NULL);
}

void start_dinner(t_table *table)
{
    int i;
    
    i = -1;
    if (table->nbr_limit_meals == 0)
        return ;
    else if (table->philo_nbr == 1)
    {
        write_status(TAKE_FIRST_FORK, &table->philos[0], DEBUG_MODE);
        precise_usleep(table->time_to_die, table);
        write_status(DIED, &table->philos[0], DEBUG_MODE);
        set_bool(&table->table_mutex, &table->end_simulation, true);
        return ;
    }
    else
    {
        while (++i < table->philo_nbr)  
            safe_thread_handle(&table->philos[i].thread_id, dinner_simu,
                &table->philos[i], CREATE);
    }
    safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
    table->start_simulation = gettime(MILLISECOND);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    i = -1;
    while(++i < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
    set_bool(&table->table_mutex, &table->end_simulation, true);
    safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
