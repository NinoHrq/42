/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:06:13 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/20 21:20:57 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

//Usage printf(BLACK "This is black text" RESET "\n");
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RST     "\033[0m"


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
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t thread_id;
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
    bool end_simulation; //moment ou un philo meurt ou si tous les philos ont mange
    t_fork *forks;
    t_philo *philos;
};

//Prototypes
    //utils.c
void error_quit(const char *error);
