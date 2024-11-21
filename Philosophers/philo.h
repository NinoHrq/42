/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:06:13 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 00:10:20 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

//Usage printf(BLACK "This is black text" RESET "\n");
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define Y       "\033[33m"
#define BLUE    "\033[34m"
#define M       "\033[35m"
#define C       "\033[36m"
#define W       "\033[37m"
#define RST     "\033[0m"

#define DEBUG_MODE 0

typedef enum s_ezcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}           t_ezcode;

typedef enum s_timecd
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}           t_timecd;

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
}       t_philo_status;
//Structures
typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef struct s_fork
{
    t_mtx fork;
    int fork_id;
}           t_fork;

typedef struct s_philo
{
    int id;
    long meals_counter;
    bool full;
    long last_meal_time;
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id;
    t_mtx philo_mutex;
    t_table *table;
}             t_philo;

struct s_table  //contient l'ensemble des data
{
    long philo_nbr;
    long time_to_die;
    long time_to_sleep;
    long time_to_eat;
    long nbr_limit_meals;
    long start_simulation; // moment ou la simulation commence
    long threads_running_nbr;
    bool end_simulation; //moment ou un philo meurt ou si tous les philos ont mange
    bool all_threads_ready;
    t_mtx table_mutex;
    t_mtx message_mutex;
    t_fork *forks;
    t_philo *philos;
    pthread_t monitor;
};

//Prototypes
    //utils.c
void error_quit(const char *error);
long gettime(t_timecd timecode);
void precise_usleep(long usec, t_table *table);
void clean(t_table *table);

    //parsing.c
void parse_input(t_table *table, char **av);

    //safe_fonctions.c
void safe_thread_handle(pthread_t *thread, void *(*foo) (void *), void *data, t_ezcode ezcode);
void safe_mutex_handle(t_mtx *mutex, t_ezcode ezcode);
void *safe_malloc(size_t bytes);

    //init.c
void data_init(t_table *table);

    //dinner.c
void *dinner_simu(void *data);
void start_dinner(t_table *table);
    
    //getters_setters.c
void set_bool(t_mtx *mutex, bool *dest, bool value);
bool get_bool(t_mtx *mutex, bool *value);
void set_long(t_mtx *mutex, long *dest, long value);
long get_long(t_mtx *mutex, long *value);
bool simu_finished(t_table *table);

    //synchro_utils.c
void  wait_for_all_threads(t_table *table);
void increase_long(t_mtx *mutex, long *value);
bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);

    //message.c
void write_status(t_philo_status status, t_philo *philo, bool debug);

    //monitoring.c
void *monitor_dinner(void *data);

#endif