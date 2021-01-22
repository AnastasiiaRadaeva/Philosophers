/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:53:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int						ft_sem_init(long number)
{
	sem_unlink(S_PRINT);
	if ((g_print = sem_open(S_PRINT, O_CREAT, O_RDWR, 1)) == SEM_FAILED)
		ft_putendl_plus_error(MUTEX_INIT, FAILURE);
	sem_unlink(S_CHECK_TIME);
	if ((g_check_time = sem_open(S_CHECK_TIME, O_CREAT, O_RDWR, 1)) == SEM_FAILED)
	{
		sem_close(g_print);
		sem_unlink(S_PRINT);
		ft_putendl_plus_error(MUTEX_INIT, FAILURE);
	}
	sem_unlink(S_FORKS);
	if ((g_forks = sem_open(S_FORKS, O_CREAT, O_RDWR, number)) == SEM_FAILED)
	{
		sem_close(g_print);
		sem_unlink(S_PRINT);
		sem_close(g_check_time);
		sem_unlink(S_CHECK_TIME);
		ft_putendl_plus_error(MUTEX_INIT, FAILURE);
	}
	sem_unlink(S_TWO_FORKS);
	if ((g_two_fork = sem_open(S_TWO_FORKS, O_CREAT, O_RDWR, 1)) == SEM_FAILED)
	{
		sem_close(g_print);
		sem_unlink(S_PRINT);
		sem_close(g_check_time);
		sem_unlink(S_CHECK_TIME);
		sem_close(g_forks);
		sem_unlink(S_FORKS);
		ft_putendl_plus_error(MUTEX_INIT, FAILURE);
	}
	return (0);
}

long					ft_g_init(void)
{
//	if (!(g_print = (sem_t *)malloc(sizeof(sem_t))))
//		ft_putendl_plus_error(MALLOC, FAILURE);
//	if (!(g_check_time = (sem_t *)malloc(sizeof(sem_t))))
//		ft_putendl_plus_error(MALLOC, FAILURE);
//	if (!(g_forks = (sem_t *)malloc(sizeof(sem_t))))
//		ft_putendl_plus_error(MALLOC, FAILURE);
//	if (!(g_two_fork = (sem_t *)malloc(sizeof(sem_t))))
//		ft_putendl_plus_error(MALLOC, FAILURE);
	g_time_to_die = start_time();
	return (0);
}

t_params				**init_params(char **args, int argc)
{
	t_params			**info;

	info = NULL;
	if (!(info = (t_params **)malloc(sizeof(t_params *))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	if (!(*info = (t_params *)malloc(sizeof(t_params))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	(*info)->number_of_philo_and_forks = ft_atoi(args[1], 1);
	(*info)->time_to_die = ft_atoi(args[2], 0);
	(*info)->time_to_eat = ft_atoi(args[3], 0);
	(*info)->time_to_sleep = ft_atoi(args[4], 0);
	(*info)->number_of_times_each_philo_must_eat = -1;
	if (argc == 6)
		(*info)->number_of_times_each_philo_must_eat = ft_atoi(args[5], 3);
	return (info);
}

t_args					*init_args(t_params ***info)
{
	t_args			*args;

	if (!(args = (t_args *)malloc(sizeof(t_args))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	args->time = start_time();
	args->info = *info;
	args->timestamp = 0;
	args->number_of_philo = 0;
	return (args);
}
