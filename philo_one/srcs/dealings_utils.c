/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:43:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/12/28 19:34:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			unlock_ret(int flag, pthread_mutex_t *mut_1, pthread_mutex_t *mut_2,
														pthread_mutex_t *mut_3)
{
	if (mut_1)
		pthread_mutex_unlock(mut_1);
	if (mut_2)
		pthread_mutex_unlock(mut_2);
	if (mut_3)
		pthread_mutex_unlock(mut_3);
	if (flag == 1)
		pthread_mutex_unlock(g_print);
	return (1);
}

static void	ft_putnbr(long n)
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

int			print_state(long name, t_timepad **time, char *str, int flag)
{
	long	t;

	if (g_close == 1 && flag == GLOBAL_ON)
		return (1);
	else
	{
		time_stop(time, &t);
		ft_putnbr((*time)->timestamp);
		write(1, "ms ", 3);
		ft_putnbr(name);
		ft_putendl_plus_error(str, g_error, NULL);
		return (0);
	}
}

void		reset_time(int number)
{
	t_timepad	*for_free;

	for_free = g_time_to_die[number];
	g_time_to_die[number] = start_time();
	free(for_free->t_start);
	free(for_free->current_t);
	free(for_free->t_zone);
	free(for_free);
}

int			take_forks(int left_fork, int right_fork, long number,
														t_timepad **time)
{
	pthread_mutex_lock(g_fork[left_fork]);
	pthread_mutex_lock(g_print);
	if (print_state(number, time, L_FORK, GLOBAL_ON) == 1)
		return (unlock_ret(1, NULL, g_fork[left_fork], NULL));
	pthread_mutex_unlock(g_print);
	pthread_mutex_lock(g_fork[right_fork]);
	pthread_mutex_lock(g_print);
	if (print_state(number, time, R_FORK, GLOBAL_ON) == 1)
		return (unlock_ret(1, g_fork[right_fork], g_fork[left_fork], NULL));
	pthread_mutex_unlock(g_print);
	return (0);
}
