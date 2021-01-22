/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:43:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 20:10:32 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			unlock_ret(int flag, int number_of_forks, int flag_2)
{
	while (--number_of_forks >= 0)
		sem_post(g_forks);
	if (flag == 1)
		sem_post(g_print);
	if (flag_2 == 1)
		sem_post(g_check_time);
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

int			take_forks(long number, t_timepad **time)
{
	sem_wait(g_two_forks);
	sem_wait(g_forks);
	sem_wait(g_print);
	if (print_state(number, time, F_FORK, GLOBAL_ON) == 1)
		return (unlock_ret(1, 1, 0));
	sem_post(g_print);
	sem_wait(g_forks);
	sem_post(g_two_forks);
	sem_wait(g_print);
	if (print_state(number, time, S_FORK, GLOBAL_ON) == 1)
		return (unlock_ret(1, 2, 1));
	return (0);
}
