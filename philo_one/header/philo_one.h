/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:30:17 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 23:05:08 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define NUM_OF_ARGS "Error: wrong number of arguments (you can use 5 or 6)."
# define NUM_OF_PH "Error: wrong number of philosophers (use 2 - 200)."
# define WRONG_RANGE "Error: you use wrong range (use 0 - 2 147 483)."
# define WRONG_FORMAT "Error: wrong format of arguments (only numbers)."
# define MALLOC "Error: malloc is failed."
# define MUTEX_INIT "Error: initialization of mutex is failed."
# define PTHREAD_CR "Error: thread wasn't created."

# define R_FORK " has taken a right fork"
# define L_FORK " has taken a left fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINK " is thinking"
# define DEATH " died"

# define GLOBAL_ON 1

typedef struct			s_params
{
	long			number_of_philo_and_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philo_must_eat;
}						t_params;

typedef struct			s_philosopher
{
	long			number;
	long			left_fork;
	long			right_fork;
	long			timestamp;
}						t_philosopher;

typedef struct			s_timepad
{
	struct timeval	*t_start;
	struct timeval	*current_t;
	long			timestamp;
	struct timezone	*t_zone;
}						t_timepad;

typedef struct			s_args
{
	t_philosopher	*philo;
	t_params		**info;
	t_timepad		**time;
}						t_args;

extern int				g_error;
extern pthread_mutex_t	*g_print;
extern t_timepad		**g_time_to_die;
extern int				g_close;
extern int				*g_number_of_meals;
extern pthread_mutex_t	**g_fork;
extern pthread_mutex_t	*g_w;

int						initialization(t_params **info, t_args ***args,
													pthread_t **thread);
void					check_term_conditions(t_args **args, t_params **info,
															int argc, long i);
int						create_threads(t_params **info, t_args **args,
													pthread_t **thread);
void					waiting_for_threads(t_params **info,
											pthread_t **thread);

t_params				**init_params(char **args, int argc);
t_args					**init_args(long number, t_params ***info);
long					ft_g_init(long number);
int						mutex_init(long number);

long					ft_atoi(char *str, int flag);
int						ft_strlen(const char *str);
void					*ft_putendl_plus_error(char *str, int flag, void *ret);
int						ft_free(t_params ***info, t_args ***args, int ret);
int						unlock_ret(int flag, pthread_mutex_t *mut_1,
								pthread_mutex_t *mut_2, pthread_mutex_t *mut_3);
void					ft_mut_destr(long number);
int						print_state(long name, t_timepad **time, char *str,
																int flag);

t_timepad				*start_time(void);
void					*time_stop(t_timepad **time, long *timestamp);
void					reset_time(int number);

void					*philosopher(void *args);
int						take_forks(int left_fork, int right_fork, long number,
															t_timepad **time);

#endif
