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

int unlock_ret(int flag, pthread_mutex_t *mut_1, pthread_mutex_t *mut_2)
{
	if (mut_1)
		pthread_mutex_unlock(mut_1);
	if (mut_2)
		pthread_mutex_unlock(mut_2);
	if (flag == 1)
		pthread_mutex_unlock(g_print);
	return (1);
}

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
	long t;

	time_stop(time, &t);
	ft_putnbr((*time)->timestamp);
	write(1, "ms ", 3);
	ft_putnbr(name);
	ft_putendl_plus_error(str, g_error, NULL);
}

int	ft_think(t_philosopher **philo, t_timepad **time)
{
	pthread_mutex_lock(g_print);
	if (g_close == 1)
		return (unlock_ret(1, NULL, NULL));
	print_state((*philo)->number, time, THINK);
	pthread_mutex_unlock(g_print);
	return (0);
}

int ft_sleep(t_philosopher **philo, long ms, t_timepad **time)
{
	pthread_mutex_lock(g_print);
	if (g_close == 1)
		return (unlock_ret(1, NULL, NULL));
	print_state((*philo)->number, time, SLEEP);
	pthread_mutex_unlock(g_print);
	if (g_close == 1)
		return (unlock_ret(0, NULL, NULL));
	usleep(ms);
	return (0);
}

int ft_eat(t_philosopher **philo, long ms, t_timepad **time, pthread_mutex_t **mut)
{
	t_timepad	*for_free;

	pthread_mutex_lock(&(*mut)[(*philo)->right_fork - 1]);
	pthread_mutex_lock(g_print);
	if (g_close == 1)
		return (unlock_ret(1, &(*mut)[(*philo)->right_fork - 1], NULL));
	print_state((*philo)->number, time, R_FORK);
	pthread_mutex_unlock(g_print);
	pthread_mutex_lock(&(*mut)[(*philo)->left_fork - 1]);
	pthread_mutex_lock(g_print);
	if (g_close == 1)
		return (unlock_ret(1, &(*mut)[(*philo)->right_fork - 1], &(*mut)[(*philo)->left_fork - 1]));
	print_state((*philo)->number, time, L_FORK);
	pthread_mutex_unlock(g_print);
	pthread_mutex_lock(g_print);
	if (g_close == 1)
		return (unlock_ret(1, &(*mut)[(*philo)->right_fork - 1], &(*mut)[(*philo)->left_fork - 1]));
	print_state((*philo)->number, time, EAT);
	for_free = g_time_to_die[(*philo)->number - 1];
	g_time_to_die[(*philo)->number - 1] = start_time();
	free(for_free->t_start);
	free(for_free->current_t);
	free(for_free->t_zone);
	free(for_free);
	pthread_mutex_unlock(g_print);
	if (g_close == 1)
		return (unlock_ret(0, &(*mut)[(*philo)->right_fork - 1], &(*mut)[(*philo)->left_fork - 1]));
	usleep(ms);
	g_number_of_meals[(*philo)->number - 1]++;
	pthread_mutex_unlock(&(*mut)[(*philo)->right_fork - 1]);
	pthread_mutex_unlock(&(*mut)[(*philo)->left_fork - 1]);
	return (0);
}

void *philosopher(void *args)
{
	t_args			*arg;

	arg = (t_args *)args;
	while (g_close == 0)
	{
		if (ft_think(&arg->philo, arg->time) == 1)
			return (NULL);
		if (ft_eat(&arg->philo, (*(arg->info))->time_to_eat, arg->time, arg->mut) == 1)
			return (NULL);
		if (ft_sleep(&arg->philo, (*(arg->info))->time_to_sleep, arg->time) == 1)
			return (NULL);
	}
	return (NULL);
}
