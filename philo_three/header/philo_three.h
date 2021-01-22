/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:48:17 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/18 23:05:08 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>

# define NUM_OF_ARGS "Error: wrong number of arguments (you can use 5 or 6)."
# define NUM_OF_PH "Error: wrong number of philosophers (use 2 - 200)."
# define WRONG_RANGE "Error: you use wrong range (use 0 - 2 147 483)."
# define WRONG_FORMAT "Error: wrong format of arguments (only numbers)."
# define MALLOC "Error: malloc is failed."
# define MUTEX_INIT "Error: initialization of mutex is failed."
# define PTHREAD_CR "Error: thread wasn't created."
# define PROCESS_CR "Error: process wasn't created."
# define SIGNAL "Error: don't use signal."

# define F_FORK " has taken a first fork"
# define S_FORK " has taken a second fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINK " is thinking"
# define DEATH " died"
# define FED "Every philosopher has eaten enough times"

# define S_PRINT "/print"
# define S_CHECK_TIME "/check_time"
# define S_FORKS "/forks"
# define S_TWO_FORKS "/two_forks"

# define SUCCESS 0
# define FAILURE 1
# define ST_DEATH 2
# define ST_FED 3
# define WITHOUT_EXIT 4


typedef struct			s_params
{
	long			number_of_philo_and_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philo_must_eat;
}						t_params;

typedef struct			s_timepad
{
	struct timeval	*t_start;
	struct timeval	*current_t;
	long			timestamp;
	struct timezone	*t_zone;
}						t_timepad;

typedef struct			s_args
{
	t_params		**info;
	t_timepad		*time;
	long 			number_of_philo;
	long 			timestamp;
}						t_args;

extern sem_t			*g_print;
extern t_timepad		*g_time_to_die;
extern int				g_number_of_meals;
extern sem_t			*g_forks;
extern sem_t			*g_check_time;
extern sem_t			*g_two_fork;

int						initialization(t_params **info, t_args **args);
void					check_term_conditions(t_args **args, t_params **info);
void 					create_thread(t_args *args, pthread_t **thread);
int						waiting_for_processes(t_params **info, pid_t **pid);

t_params				**init_params(char **args, int argc);
t_args					*init_args(t_params ***info);
long					ft_g_init(void);
int						ft_sem_init(long number);

long					ft_atoi(char *str, int flag);
int						ft_strlen(const char *str);
void					ft_putendl_plus_error(char *str, int status);
int						ft_free(t_params ***info, t_args **args, pid_t **pid, int ret);
void					ft_sem_destr(void);
int						print_state(long name, t_timepad **time, char *str);

t_timepad				*start_time(void);
void					*time_stop(t_timepad **time, long *timestamp);
void					reset_time(void);

void					*philosopher(void *args);
int						take_forks(long number, t_timepad **time);

#endif
