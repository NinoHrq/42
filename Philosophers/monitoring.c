/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:06:41 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 00:30:07 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool philo_death(t_philo *philo)
{
    long past;
    long t_to_die;
    
    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    past = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    t_to_die = philo->table->time_to_die / 1e3;
    if(past > t_to_die)
        return (true);
    return (false);
}
void *monitor_dinner(void *data)
{
    int i;
    t_table *table;
    
    table = (t_table *)data;
    while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr, 
        table->philo_nbr))
        ;
    while(!simu_finished(table))
    {
        i = -1;
        while (++i < table->philo_nbr && !simu_finished(table))
        {
            if(philo_death(&table->philos[i]))
            {
                set_bool(&table->table_mutex, &table->end_simulation, true);
                write_status(DIED, &table->philos[i], DEBUG_MODE);
            }
        }
    }
    return(NULL);
}
