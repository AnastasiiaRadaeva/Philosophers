/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:49:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:51:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				g_number_of_meals = 0;
sem_t			*g_print = NULL;
sem_t			*g_forks = NULL;
sem_t			*g_two_fork = NULL;
sem_t			*g_check_time = NULL;
t_timepad		*g_time_to_die = NULL;

void	create_thread(t_args *args)
{
	pthread_t	*thread;

	if (!(thread = (pthread_t *)malloc(sizeof(pthread_t))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	if (pthread_create(thread, NULL, philosopher, args))
	{
		ft_sem_destr();
		ft_putendl_plus_error(PTHREAD_CR, FAILURE);
	}
}

void ft_process(t_args **args, long number_of_philo)
{
	(*args)->number_of_philo = number_of_philo;
	create_thread(*args);
//	philosopher(*args);
	check_term_conditions(args, (*args)->info);
}

void create_processes(pid_t **pid, t_params **info, t_args **args)
{
	long i;

	i = -1;
	while (++i < (*info)->number_of_philo_and_forks)
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
			ft_putendl_plus_error(PROCESS_CR, FAILURE);
		else if ((*pid)[i] == 0)
			ft_process(args, i + 1);
	}
}

int				main(int argc, char *argv[])
{
	t_params	**info;
	t_args		*args;
	pid_t		*pid;

	info = NULL;
	args = NULL;
	pid = NULL;

//	if (argc == 1)
//	{
//		(void)argv;
//		char *array[6];
//
//		array[0] = "a";
//		array[1] = "2";
//		array[2] = "500";
//		array[3] = "100";
//		array[4] = "100";
//		array[5] = "2";
//
//		argc = 5;
	if (argc == 5 || argc == 6)
	{
		info = init_params(argv, argc);
		if (!(pid = (pid_t *)malloc(sizeof(pid) * (*info)->number_of_philo_and_forks)))
			ft_putendl_plus_error(MALLOC, FAILURE);
		initialization(info, &args);
		create_processes(&pid, info, &args);
		if (waiting_for_processes(info, &pid) == ST_FED)
			ft_putendl_plus_error(FED, WITHOUT_EXIT);
		ft_sem_destr();
	}
	else
		ft_putendl_plus_error(NUM_OF_ARGS, SUCCESS);
	return (ft_free(&info, &args, &pid, 0));
}

