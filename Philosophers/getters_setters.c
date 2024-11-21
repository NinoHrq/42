/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:01:29 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 21:04:03 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void set_bool(t_mtx *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool get_bool(t_mtx *mutex, bool *value)
{
    bool ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}

void set_long(t_mtx *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

long get_long(t_mtx *mutex, long *value)
{
    long ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return(ret);
}

bool simu_finished(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}