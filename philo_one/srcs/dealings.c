/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:17:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/12/28 19:34:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

//каждому дейсвию поставить сообщение и сделать глобальную переменную, которая не даст сразу всем процессам печатать свое состояние.

void	ft_putnbr(long n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
}

void 	print_state(long name, t_timepad **time, char *str)
{
	time_stop(time);
	ft_putnbr((*time)->timestamp);
	write(1, "ms ", 3);
	ft_putnbr(name);
	ft_putendl_plus_error(str, g_error);
}

void	ft_think(t_philosopher **philo, t_params **info, t_timepad **time)
{
	(*philo)->state = thinking;
	pthread_mutex_lock(g_print);
	print_state((*philo)->number, time, THINK);
	pthread_mutex_unlock(g_print);
}

void	ft_sleep(t_philosopher **philo, t_params **info, t_timepad **time)
{
	(*philo)->state = sleeping;
	pthread_mutex_lock(g_print);
	print_state((*philo)->number, time, SLEEP);
	pthread_mutex_unlock(g_print);
	usleep((*info)->time_to_sleep);
}

void	ft_eat(t_philosopher **philo, t_params **info, t_timepad **time, pthread_mutex_t **mut)
{
	pthread_mutex_lock(mut[(*philo)->right_fork]);
	pthread_mutex_lock(g_print);
	print_state((*philo)->number, time, R_FORK);
	pthread_mutex_unlock(g_print);
	pthread_mutex_lock(mut[(*philo)->left_fork]);
	pthread_mutex_lock(g_print);
	print_state((*philo)->number, time, L_FORK);
	pthread_mutex_unlock(g_print);
	(*philo)->state = eating;
	pthread_mutex_lock(g_print);
	print_state((*philo)->number, time, EAT);
	g_time_to_die = start_time();
	g_time_to_die->name_of_philo = (*philo)->number;
	pthread_mutex_unlock(g_print);
	usleep((*info)->time_to_eat);
	pthread_mutex_unlock(mut[(*philo)->right_fork]);
	pthread_mutex_unlock(mut[(*philo)->left_fork]);
}

void *philosopher(void *args)
{
	t_args			*arg;

	arg = (t_args *)args;
	ft_think(&arg->philo, arg->info, arg->time);
	ft_eat(&arg->philo, arg->info, arg->time, arg->mut);
	ft_sleep(&arg->philo, arg->info, arg->time);
}
