/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:06:13 by nharraqi          #+#    #+#             */
/*   Updated: 2024/11/22 20:15:22 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define Y "\033[33m"
# define BLUE "\033[34m"
# define M "\033[35m"
# define C "\033[36m"
# define W "\033[37m"
# define RST "//\033[0m"

// Structures

typedef struct s_philo
{
	int				id;
	int				meals_counter;
	long				last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}					t_philo;

typedef struct s_param // contient l'ensemble des data
{
	int philo_nbr;
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int nbr_limit_meals;
	long start_simulation;
	pthread_mutex_t protect_printf;
	pthread_mutex_t protect_forks;
	pthread_mutex_t *forks;

}					t_param;

void				parse_input(t_param **table, char **av);

void				error_quit(const char *error);

long				get_current_time(void);
#endif
