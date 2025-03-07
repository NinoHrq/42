/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:06:13 by nharraqi          #+#    #+#             */
/*   Updated: 2025/03/07 19:20:49 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals_counter;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_param	*param;
}					t_philo;

typedef struct s_param
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nbr_limit_meals;
	int				p_dead;
	long			start_simulation;
	pthread_mutex_t	protect_printf;
	pthread_mutex_t	protect_forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect_dead;

}					t_param;

// parsing.c
void				parse_input(t_param **table, char **av);
int					parse_philo(t_param *param, t_philo *philo);
long				ft_atol(const char *str, t_param *param);

// utils.c
void				error_quit(const char *error, t_param *param);
long				get_current_time(void);
void				only_one(t_param *param, t_philo *philo, long time);
void				printd_dead(t_param *param, t_philo *philo, long time);

// main.c
int					check_param(int ac, char **av);
void				free_all(t_param *param, t_philo *philo);

// routine.c
void				*routine(void *arg);
void				eat_infinite(t_param *param, t_philo *philo);
void				eat_your_meals(t_param *param, t_philo *philo);
void				dinner(t_param *param, t_philo *philo);
void				after_forks(t_param *param, t_philo *philo);

// routine_2.c
void				take_forks_even(t_param *param, t_philo *philo);
void				take_forks_odd(t_param *param, t_philo *philo);
void				for_eat(t_philo *philo, t_param *param, long time);
void				for_sleep(t_philo *philo, t_param *param, long time);
void				for_think(t_philo *philo, t_param *param, long time);

// spe_case.c
void				spe_case(t_param *param, t_philo *philo, char c);
void				eat_sup_die(t_param *param, t_philo *philo);
void				after_forks_spe_eat(t_param *param, t_philo *philo);
void				sleep_sup_die(t_param *param, t_philo *philo);
void				after_forks_spe_sleep(t_param *param, t_philo *philo);

#endif
