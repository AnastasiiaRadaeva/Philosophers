/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:53:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int						ft_sem_init(long number)
{
	sem_unlink(S_PRINT);
	if ((g_print = sem_open(S_PRINT, O_CREAT, O_RDWR, 1)) == SEM_FAILED)
		return ((int)(ft_putendl_plus_error(MUTEX_INIT, -1, (void *)1)));
	sem_unlink(S_CHECK_TIME);
	if ((g_check_time = sem_open(S_CHECK_TIME, O_CREAT, O_RDWR, 1)) == SEM_FAILED)
	{
		sem_close(g_print);
		sem_unlink(S_PRINT);
		return ((int)(ft_putendl_plus_error(MUTEX_INIT, -1, (void *)1)));
	}
	sem_unlink(S_FORKS);
	if ((g_forks = sem_open(S_FORKS, O_CREAT, O_RDWR, number)) == SEM_FAILED)
	{
		sem_close(g_print);
		sem_unlink(S_PRINT);
		sem_close(g_check_time);
		sem_unlink(S_CHECK_TIME);
		return ((int)(ft_putendl_plus_error(MUTEX_INIT, -1, (void *)1)));
	}
	return (0);
}

long					ft_g_init(long number)
{
	long	i;

	i = -1;
	if (!(g_number_of_meals = (int *)malloc(sizeof(int) * number)))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	while (++i < number)
		g_number_of_meals[i] = 0;
//	if (!(g_print = (sem_t *)malloc(sizeof(sem_t))))
//		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
//	if (!(g_check_time = (sem_t *)malloc(sizeof(sem_t))))
//		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	if (!(g_time_to_die = (t_timepad **)malloc(sizeof(t_timepad *) * number)))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	i = -1;
	while (++i < number)
		if (!(g_time_to_die[i] = start_time()))
			return (1);
//	if (!(g_forks = (sem_t *)malloc(sizeof(sem_t))))
//		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	return (0);
}

t_params				**init_params(char **args, int argc)
{
	t_params			**info;

	info = NULL;
	if (!(info = (t_params **)malloc(sizeof(t_params *))))
		return ((t_params **)ft_putendl_plus_error(MALLOC, -1, NULL));
	if (!(*info = (t_params *)malloc(sizeof(t_params))))
		return ((t_params **)ft_putendl_plus_error(MALLOC, -1, NULL));
	(*info)->number_of_philo_and_forks = ft_atoi(args[1], 1);
	(*info)->time_to_die = ft_atoi(args[2], 0);
	(*info)->time_to_eat = ft_atoi(args[3], 0);
	(*info)->time_to_sleep = ft_atoi(args[4], 0);
	(*info)->number_of_times_each_philo_must_eat = 1;
	if (g_error == -1)
	{
		ft_free(&info, NULL, 0);
		return (NULL);
	}
	if (argc == 6)
		(*info)->number_of_times_each_philo_must_eat = ft_atoi(args[5], 3);
	return (info);
}

static t_philosopher	*init_philo(long index)
{
	t_philosopher		*philo;

	if (!(philo = (t_philosopher *)malloc(sizeof(t_philosopher))))
		return ((t_philosopher *)ft_putendl_plus_error(MALLOC, -1, NULL));
	philo->number = index + 1;
	philo->timestamp = 0;
	return (philo);
}

t_args					**init_args(long number, t_params ***info)
{
	long			index;
	t_args			**args;
	t_timepad		**time;

	index = -1;
	if (number < 1)
		return (NULL);
	if (!(time = (t_timepad **)malloc(sizeof(t_timepad *))))
		return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
	if (!(*time = start_time()))
		return (NULL);
	index = -1;
	if (!(args = (t_args **)malloc(sizeof(t_args *) * number)))
		return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
	while (++index < number)
	{
		if (!(args[index] = (t_args *)malloc(sizeof(t_args))))
			return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
		args[index]->philo = init_philo(index);
		args[index]->info = *info;
		args[index]->time = time;
	}
	return (args);
}
