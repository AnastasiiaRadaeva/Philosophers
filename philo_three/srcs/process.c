/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:17:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/22 20:37:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	tracking_philo(t_args **args, t_params **info)
{
	while (1)
	{
		sem_wait(g_check_time);
		time_stop(&(g_time_to_die), &((*args)->timestamp));
		sem_post(g_check_time);
		if ((*args)->timestamp >= (((*info)->time_to_die) / 1000))
		{
			sem_wait(g_print);
			print_state((*args)->number_of_philo, &((*args)->time), DEATH);
			exit(ST_DEATH);
		}
		if (g_number_of_meals >= (*info)->number_of_times_each_philo_must_eat
						&& (*info)->number_of_times_each_philo_must_eat != -1)
		{
			sem_wait(g_print);
			exit(ST_FED);
		}
	}
}

static void	create_philo_thread(t_args *args, pthread_t **thread)
{
	if (!(*thread = (pthread_t *)malloc(sizeof(pthread_t))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	if (pthread_create(*thread, NULL, philosopher, args))
	{
		ft_sem_destr();
		ft_putendl_plus_error(PTHREAD_CR, FAILURE);
	}
}

void		ft_process(t_args **args, long number_of_philo, pthread_t **thread)
{
	(*args)->number_of_philo = number_of_philo;
	create_philo_thread(*args, thread);
	tracking_philo(args, (*args)->info);
}
