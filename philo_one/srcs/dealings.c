/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:17:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/01/17 22:45:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_think(t_philosopher **philo, t_timepad **time)
{
	pthread_mutex_lock(g_print);
	if (print_state((*philo)->number, time, THINK, GLOBAL_ON) == 1)
		return (unlock_ret(1, NULL, NULL, NULL));
	pthread_mutex_unlock(g_print);
	return (0);
}

static int	ft_sleep(t_philosopher **philo, long ms, t_timepad **time)
{
	pthread_mutex_lock(g_print);
	if (print_state((*philo)->number, time, SLEEP, GLOBAL_ON) == 1)
		return (unlock_ret(1, NULL, NULL, NULL));
	pthread_mutex_unlock(g_print);
	if (g_close == 1)
		return (unlock_ret(0, NULL, NULL, NULL));
	usleep(ms);
	return (0);
}

static int	ft_eat(t_philosopher **philo, long ms, t_timepad **time)
{
	if (take_forks((int)((*philo)->left_fork - 1),
				(int)((*philo)->right_fork - 1), (*philo)->number, time) == 1)
		return (1);
	pthread_mutex_lock(g_print);
	if (print_state((*philo)->number, time, EAT, GLOBAL_ON) == 1)
	{
		return (unlock_ret(1, g_fork[(*philo)->right_fork - 1],
								g_fork[(*philo)->left_fork - 1], NULL));
	}
	pthread_mutex_unlock(g_print);
	pthread_mutex_lock(g_w);
	reset_time((int)((*philo)->number - 1));
	pthread_mutex_unlock(g_w);
	usleep(ms);
	g_number_of_meals[(*philo)->number - 1]++;
	pthread_mutex_unlock(g_fork[(*philo)->right_fork - 1]);
	pthread_mutex_unlock(g_fork[(*philo)->left_fork - 1]);
	return (0);
}

void		*philosopher(void *args)
{
	t_args			*arg;

	arg = (t_args *)args;
	while (g_close == 0)
	{
		ft_think(&arg->philo, arg->time);
		ft_eat(&arg->philo, (*(arg->info))->time_to_eat, arg->time);
		ft_sleep(&arg->philo, (*(arg->info))->time_to_sleep, arg->time);
	}
	return (NULL);
}
