/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:09:03 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 00:36:18 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_quit(const char *error)
{
    printf(RED"%s\n"RST, error);
    exit(EXIT_FAILURE);
}

long gettime(t_timecd timecode)
{
    struct timeval tval;
    
    if (gettimeofday(&tval, NULL) == -1)
        error_quit("Getimeofday failed");
    if (timecode == SECOND)
        return (tval.tv_sec + (tval.tv_usec / 1e6));
    if (timecode == MILLISECOND)
        return ((tval.tv_sec * 1e3) + (tval.tv_usec / 1e3));
    if (timecode == MICROSECOND)
        return ((tval.tv_sec * 1e6) + tval.tv_usec);
    else
        error_quit("WRONG INPUT");
    return (-1);
}

void precise_usleep(long usec, t_table *table)
{
    long start;
    long past;
    long still;

    start = gettime(MICROSECOND);
    while(gettime(MICROSECOND) - start < usec)
    {
        if (simu_finished(table))
            break;
        past = gettime(MICROSECOND) - start;
        still = usec - past;
        if(still > 1e3)
            usleep(still / 2);
        else
        {
            while (gettime(MICROSECOND) - start < usec)
            {
                if (simu_finished(table))
                    break;
                usleep(100); // Intervalle raisonnable pour éviter la surcharge
            }
        }        
    }
}

void clean(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbr)
        safe_mutex_handle(&table->philos[i].philo_mutex, DESTROY);
    safe_mutex_handle(&table->table_mutex, DESTROY);
    safe_mutex_handle(&table->forks[i].fork, DESTROY);
    safe_mutex_handle(&table->message_mutex, DESTROY);
    free(table->philos);
    free(table->forks);
}
