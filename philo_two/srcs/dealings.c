/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:17:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:45:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_think(t_philosopher **philo, t_timepad **time)
{
	sem_wait(g_print);
	if (print_state((*philo)->number, time, THINK, GLOBAL_ON) == 1)
		return (unlock_ret(1, 0, 0));
	sem_post(g_print);
	return (0);
}

static int	ft_sleep(t_philosopher **philo, long ms, t_timepad **time)
{
	sem_wait(g_print);
	if (print_state((*philo)->number, time, SLEEP, GLOBAL_ON) == 1)
		return (unlock_ret(1, 0, 0));
	sem_post(g_print);
	if (g_close == 1)
		return (1);
	usleep(ms);
	return (0);
}

static int	ft_eat(t_philosopher **philo, long ms, t_timepad **time)
{
	if (take_forks((*philo)->number, time) == 1)
		return (1);
//	sem_wait(g_print);
	if (print_state((*philo)->number, time, EAT, GLOBAL_ON) == 1)
		return (unlock_ret(1, 2, 0));
	sem_post(g_print);
	sem_wait(g_check_time);
	reset_time((int)((*philo)->number - 1));
	sem_post(g_check_time);
	usleep(ms);
	g_number_of_meals[(*philo)->number - 1]++;
	sem_post(g_forks);
	sem_post(g_forks);
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
