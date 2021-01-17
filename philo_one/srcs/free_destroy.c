/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:11:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:59:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	free_time(t_args ***args)
{
	if (args && *args && (*args)[0] && *((*args)[0]->time))
	{
		if ((*((*args)[0]->time))->t_start)
			free((*((*args)[0]->time))->t_start);
		if ((*((*args)[0]->time))->current_t)
			free((*((*args)[0]->time))->current_t);
		if ((*((*args)[0]->time))->t_zone)
			free((*((*args)[0]->time))->t_zone);
		free(*((*args)[0]->time));
		free(&(*((*args)[0]->time)));
	}
}

static void	free_global_inside(long number)
{
	if (g_time_to_die && g_time_to_die[number])
	{
		if (g_time_to_die[number]->t_zone)
			free(g_time_to_die[number]->t_zone);
		if (g_time_to_die[number]->current_t)
			free(g_time_to_die[number]->current_t);
		if (g_time_to_die[number]->t_start)
			free(g_time_to_die[number]->t_start);
		free(g_time_to_die[number]);
	}
	if (g_fork && g_fork[number])
		free(g_fork[number]);
}

static void	free_global(void)
{
	if (g_number_of_meals)
		free(g_number_of_meals);
	if (g_print)
		free(g_print);
	if (g_w)
		free(g_w);
	if (g_time_to_die)
		free(g_time_to_die);
	if (g_fork)
		free(g_fork);
}

int			ft_free(t_params ***info, t_args ***args, int ret)
{
	long number;

	free_time(args);
	if (info && *info)
	{
		number = (**info)->number_of_philo_and_forks;
		free(**info);
		free(*info);
		while (--number >= 0)
		{
			if (args && *args && (*args)[number] && (*args)[number]->philo)
			{
				free((*args)[number]->philo);
				free((*args)[number]);
			}
			free_global_inside(number);
		}
	}
	if (args && *args)
		free(*args);
	free_global();
	return (ret);
}

void		ft_mut_destr(long number)
{
	long i;

	i = -1;
	while (++i < number)
		pthread_mutex_destroy(g_fork[i]);
	pthread_mutex_destroy(g_print);
	pthread_mutex_destroy(g_w);
}
