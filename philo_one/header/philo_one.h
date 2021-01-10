/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:30:17 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/12/28 19:33:08 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h> //для memset
# include <sys/time.h> //для gettimeofday
# include <pthread.h>
# include <stdlib.h> //для malloc

#include <stdio.h>

# define NUM_OF_ARGS "Error: wrong number of arguments (you can use 5 or 6)."
# define NUM_OF_PH "Error: wrong number of philosophers (use 2 - 200)."
# define WRONG_RANGE "Error: you use wrong range (use 0 - 2 147 483)."
# define WRONG_FORMAT "Error: wrong format of arguments (only numbers)."
# define MALLOC "Error: malloc is failed."
# define MUTEX_INIT "Error: initialization of mutex is failed."

# define R_FORK " has taken a right fork"
# define L_FORK " has taken a left fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINK " is thinking"
# define DEATH " died"

typedef struct 		s_params
{
	long			number_of_philo_and_forks;
	long			time_to_die;
	/*
	 * is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
	 * milliseconds after starting his last meal or the beginning
	 * of the simulation, it dies
	 */
	long			time_to_eat;
	long			time_to_sleep;
	long 			number_of_times_each_philo_must_eat;
	/*
	 * argument is optional, if all philosophers eat at least
	 * ’number_of_times_each_philosopher_must_eat’ the simulation will stop.
	 * If not specified, the simulation will stop only at the death
	 * of a philosopher.
	 */
}					t_params;

typedef struct		s_philosopher
{
	long			number;
	long 			left_fork;
	long 			right_fork;
	long 			timestamp;
}					t_philosopher;

typedef struct		s_timepad
{
	struct timeval	*t_start;
	struct timeval	*current_t;
	long 			timestamp;
	struct timezone	*t_zone;
}					t_timepad;

typedef struct		s_args
{
	t_philosopher	*philo;
	pthread_mutex_t	**mut;
	t_params		**info;
	t_timepad		**time;
}					t_args;

extern int				g_error;
extern pthread_mutex_t	*g_print;
extern t_timepad		**g_time_to_die;
extern int 				g_close;
extern int 				*g_number_of_meals;
extern long 			*g_timestamp;

long		ft_atoi(char *str, int flag);
int			ft_strlen(const char *str);
void		ft_putendl_plus_error(char *str, int flag);
t_timepad	*start_time(void);
void		*time_stop(t_timepad **time, long *timestamp);
int			ft_free(t_params ***info,/* t_timepad **time, */t_args ***args, int ret);
int 		ft_think(t_philosopher **philo, t_timepad **time);
int 		ft_sleep(t_philosopher **philo, long ms, t_timepad **time);
int 		ft_eat(t_philosopher **philo, long ms, t_timepad **time, pthread_mutex_t **mut);
void		*philosopher(void *args);
void		ft_putnbr(long n);
void 		print_state(long name, t_timepad **time, char *str);
int			unlock_ret(int flag, pthread_mutex_t *mut_1, pthread_mutex_t *mut_2);


#endif
