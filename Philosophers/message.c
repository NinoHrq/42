/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:12:00 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 19:19:58 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long past)
{
    if (!simu_finished(philo->table))
    {
        if (status == TAKE_FIRST_FORK)
            printf(W"%-6ld"RST" Philo %d has taken the 1° fork [%d]\n", 
                past, philo->id, philo->first_fork->fork_id);
        else if (status == TAKE_SECOND_FORK)
            printf(W"%-6ld"RST" Philo %d has taken the 2° fork [%d]\n",
                past, philo->id, philo->second_fork->fork_id);
        else if (status == EATING)
            printf(W"%-6ld"C" Philo %d is eating meal number [%ld]\n"RST,
                past, philo->id, philo->meals_counter);
        else if (status == SLEEPING)
            printf(W"%-6ld"Y" Philo %d is sleeping \n", past, philo->id);
        else if (status == THINKING)
            printf(W"%-6ld"M" Philo %d is thinking\n"RST, past, philo->id);
        else if (status == DIED)
            printf(W"%6ld"RED" Philo %d died\n"RST, past, philo->id);
    }
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long past;
   
    past = gettime(MILLISECOND) - philo->table->start_simulation;
    if(philo->full)
        return ;
    safe_mutex_handle(&philo->table->message_mutex, LOCK);
    if (debug)
        write_status_debug(status, philo, past);
    else if (!simu_finished(philo->table))
    {
        if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
            printf(W"%-6ld"RST" Philo %d has taken a fork\n", past, philo->id);
        else if (status == EATING)
            printf(W "%-6ld"C" Philo %d is eating\n"RST, past, philo->id);
        else if (status == SLEEPING)
            printf(W"%-6ld"Y" Philo %d is sleeping\n"RST, past, philo->id);
        else if (status == THINKING)
            printf(W"%-6ld"M" Philo %d is thinking\n"RST, past, philo->id);
        else if (DIED == status)
            printf(W"%-6ld"RED" Philo %d died\n"RST, past, philo->id);
    }
    safe_mutex_handle(&philo->table->message_mutex, UNLOCK);
}
