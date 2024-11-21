/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 23:57:59 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/21 19:07:28 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *safe_malloc(size_t bytes)
{
    void *ret;
    
    ret = malloc(bytes);
    if (NULL == ret)
        error_quit("Malloc error");
    return (ret);
}

static void handle_mutex_error(int status, t_ezcode ezcode)
{
    if (status == 0)
        return ;
    if (status == EINVAL && (ezcode == LOCK || ezcode == UNLOCK))
        error_quit("The value specified by mutex is invalid");
    else if (status == EINVAL && (ezcode == INIT || ezcode == DESTROY))
        error_quit("The value specified by attr is invalid");
    else if (status == EDEADLK)
        error_quit("A deadlock would occur if the thread blocked waiting for mutex.");
     else if (status == EPERM)
        error_quit("The current thread does not hold a lock on mutex.");
     else if (status == ENOMEM)
        error_quit("The process cannot allocate enough memory to create another mutex.");
     else if (status == EBUSY)
        error_quit("Mutex is locked.");
}


void safe_mutex_handle(t_mtx *mutex, t_ezcode ezcode)
{
    if(LOCK == ezcode)
        handle_mutex_error(pthread_mutex_lock(mutex), ezcode);
    else if(UNLOCK == ezcode)
        handle_mutex_error(pthread_mutex_unlock(mutex), ezcode);
    else if(INIT == ezcode)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), ezcode);
    else if(DESTROY == ezcode)
        handle_mutex_error(pthread_mutex_destroy(mutex), ezcode);
    else
        error_quit("Wrong opcode for thread_handle:"
            "use <LOCK> <UNLOCK> <DESTROY> or <INIT>");
}

static void handle_thread_error(int status, t_ezcode ezcode)
{
    if (0 == status)
        return ;
    if (EAGAIN == status)
        error_quit( "No resources to create another thread");
    else if (EPERM == status)
        error_quit("The caller does not have appropriate permission\n");
    else if (EINVAL == status && CREATE == ezcode)
        error_quit( "The value specified by attr is invalid.");
    else if (EINVAL == status && (JOIN == ezcode || DETACH == ezcode) )
        error_quit( "The value specified by thread is not joinable\n");
    else if (ESRCH == status)
        error_quit( "No thread could be found corresponding to that"
            "specified by the given thread ID, thread.");
    else if (EDEADLK == status)
        error_quit( "A deadlock was detected or the value of"
            "thread specifies the calling thread.");
}

void safe_thread_handle(pthread_t *thread, void *(*foo) (void *), void *data, t_ezcode ezcode)
{
    if (CREATE == ezcode)
        handle_thread_error(pthread_create(thread, NULL, foo, data), ezcode);
    else if (JOIN == ezcode)
        handle_thread_error(pthread_join(*thread, NULL), ezcode);
    else if (DETACH == ezcode)
        handle_thread_error(pthread_detach(*thread), ezcode);
    else
        error_quit("Wrong opcode for thread_handle:"
            "use <CREATE> <JOIN> or <DETACH>");
}