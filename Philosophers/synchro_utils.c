/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:18:45 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 21:24:16 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  wait_for_all_threads(t_table *table)
{
    long start;
    
    start = gettime(MILLISECOND);
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
    {
        if (gettime(MILLISECOND) - start > 5000) // Timeout après 5 secondes
            error_quit("Timeout while waiting for threads to be ready");
    }
}

bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool ret;
    
    ret = false;
    safe_mutex_handle(mutex, LOCK);
    if(*threads == philo_nbr)
        ret = true;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);   
}

void increase_long(t_mtx *mutex, long *value)
{
    safe_mutex_handle(mutex, LOCK);
    (*value)++;
    safe_mutex_handle(mutex, UNLOCK);
}
