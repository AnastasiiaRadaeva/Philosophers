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

void	ft_think(t_philosopher **philo, t_params **info)
{
	(*philo)->state = thinking;


}

void	ft_sleep(t_philosopher **philo, t_params **info)
{
	(*philo)->state = sleeping;
	usleep(info->time_to_sleep);
}

void	ft_eat(t_philosopher **philo, t_params **info)
{
	(*philo)->state = eating;
	usleep(info->time_to_eat);
}

void *philosopher(void *args)
{
	t_args			*arg;
	t_philosopher	**philo;
	t_params		**info;

	arg = (t_args *)args;
	*philo = arg->philo;
	info = arg->info;
	ft_think(philo, info);
	ft_eat(philo, info);
	ft_sleep(philo, info);
}
