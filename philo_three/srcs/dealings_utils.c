/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:49:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/22 20:26:32 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int			print_state(long name, t_timepad **time, char *str)
{
	long	t;

	time_stop(time, &t);
	ft_putnbr((*time)->timestamp);
	write(1, "ms ", 3);
	ft_putnbr(name);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (0);
}

void		reset_time(void)
{
	t_timepad	*for_free;

	for_free = g_time_to_die;
	g_time_to_die = start_time();
	free(for_free->t_start);
	free(for_free->current_t);
	free(for_free->t_zone);
	free(for_free);
}

int			take_forks(long number, t_timepad **time)
{
	sem_wait(g_two_fork);
	sem_wait(g_forks);
	sem_wait(g_print);
	print_state(number, time, F_FORK);
	sem_post(g_print);
	sem_wait(g_forks);
	sem_wait(g_print);
	print_state(number, time, S_FORK);
	sem_post(g_print);
	return (0);
}
