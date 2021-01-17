/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/01/17 22:53:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int						mutex_init(long number)
{
	long	i;

	i = -1;
	if (pthread_mutex_init(g_print, NULL))
		return ((int)(ft_putendl_plus_error(MUTEX_INIT, -1, (void *)1)));
	if (pthread_mutex_init(g_w, NULL))
	{
		pthread_mutex_destroy(g_print);
		return ((int)(ft_putendl_plus_error(MUTEX_INIT, -1, (void *)1)));
	}
	while (++i < number)
		if (pthread_mutex_init(g_fork[i], NULL))
		{
			pthread_mutex_destroy(g_print);
			pthread_mutex_destroy(g_w);
			while (--i >= 0)
				pthread_mutex_destroy(g_fork[i]);
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
	if (!(g_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	if (!(g_w = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	if (!(g_time_to_die = (t_timepad **)malloc(sizeof(t_timepad *) * number)))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	i = -1;
	while (++i < number)
		if (!(g_time_to_die[i] = start_time()))
			return (1);
	if (!(g_fork = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
																* number)))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	i = -1;
	while (++i < number)
		if (!(g_fork[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
			return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
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

static t_philosopher	*init_philo(long number, long index)
{
	t_philosopher		*philo;

	if (!(philo = (t_philosopher *)malloc(sizeof(t_philosopher))))
		return ((t_philosopher *)ft_putendl_plus_error(MALLOC, -1, NULL));
	philo->number = index + 1;
	if (index == 0)
		philo->left_fork = number;
	else
		philo->left_fork = index;
	philo->right_fork = index + 1;
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
		args[index]->philo = init_philo(number, index);
		args[index]->info = *info;
		args[index]->time = time;
	}
	return (args);
}
