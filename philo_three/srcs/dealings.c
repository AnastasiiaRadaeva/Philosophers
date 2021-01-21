/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:48:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:45:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_think(t_args **args, t_timepad **time)
{
	sem_wait(g_print);
	print_state((*args)->number_of_philo, time, THINK);
	sem_post(g_print);
	return (0);
}

static int	ft_sleep(t_args **args, long ms, t_timepad **time)
{
	sem_wait(g_print);
	print_state((*args)->number_of_philo, time, SLEEP);
	sem_post(g_print);
	usleep(ms);
	return (0);
}

static int	ft_eat(t_args **args, long ms, t_timepad **time)
{
	take_forks((*args)->number_of_philo, time);
	sem_wait(g_print);
	print_state((*args)->number_of_philo, time, EAT);
	sem_post(g_print);
	sem_post(g_two_fork);
	sem_wait(g_check_time);
	reset_time();
	sem_post(g_check_time);
	usleep(ms);
	g_number_of_meals++;
	sem_post(g_forks);
	sem_post(g_forks);
	return (0);
}

void		*philosopher(void *args)
{
	t_args			*arg;

	arg = (t_args *)args;
	while (1)
	{
		ft_think(&arg, &(arg->time));
		ft_eat(&arg, (*(arg->info))->time_to_eat, &(arg->time));
		ft_sleep(&arg, (*(arg->info))->time_to_sleep, &(arg->time));
	}
	return (NULL);
}
