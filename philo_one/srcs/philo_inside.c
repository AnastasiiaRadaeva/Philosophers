/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:43:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/01/17 22:51:50 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			initialization(t_params **info, t_args ***args, pthread_t **thread)
{
	if (ft_g_init((*info)->number_of_philo_and_forks) == 1)
		return (1);
	if (!(*thread = (pthread_t *)malloc((sizeof(pthread_t) *
										(*info)->number_of_philo_and_forks))))
		return ((int)(ft_putendl_plus_error(MALLOC, -1, (void *)1)));
	if (!(*args = init_args((*info)->number_of_philo_and_forks, &info)))
		return (1);
	if (mutex_init((*info)->number_of_philo_and_forks))
		return (1);
	return (0);
}

static void	print_end_of_the_program(long number_of_philo_who_ate,
									t_params **info, t_args **args, long number)
{
	pthread_mutex_lock(g_print);
	g_close = 1;
	if (number_of_philo_who_ate < (*info)->number_of_philo_and_forks)
		print_state(args[number]->philo->number, args[0]->time, DEATH, 0);
	else
		ft_putendl_plus_error("Every philosopher has eaten enough times\n",
																g_error, 0);
	pthread_mutex_unlock(g_print);
}

void		check_term_conditions(t_args **args, t_params **info,
														int argc, long i)
{
	long	number_of_philo_who_ate;
	int		c;

	number_of_philo_who_ate = 0;
	while ((args[i]->philo->timestamp <= (((*info)->time_to_die) / 1000))
			&& (number_of_philo_who_ate < (*info)->number_of_philo_and_forks))
	{
		if (i == (*info)->number_of_philo_and_forks - 1)
			i = 0;
		else
			i++;
		pthread_mutex_lock(g_w);
		time_stop(&(g_time_to_die[i]), &(args[i]->philo->timestamp));
		pthread_mutex_unlock(g_w);
		if (argc == 6)
		{
			c = -1;
			number_of_philo_who_ate = 0;
			while (++c < (*info)->number_of_philo_and_forks)
				if (g_number_of_meals[c] >=
					(*info)->number_of_times_each_philo_must_eat)
					number_of_philo_who_ate++;
		}
	}
	print_end_of_the_program(number_of_philo_who_ate, info, args, i);
}

int			create_threads(t_params **info, t_args **args, pthread_t **thread)
{
	long i;

	i = -1;
	while (++i < (*info)->number_of_philo_and_forks)
	{
		if (pthread_create(&(*thread)[i], NULL, philosopher, args[i]))
		{
			free(*thread);
			ft_mut_destr((*info)->number_of_philo_and_forks);
			return ((int)ft_putendl_plus_error(PTHREAD_CR, -1, (void *)1));
		}
		usleep(10);
	}
	return (0);
}

void		waiting_for_threads(t_params **info, pthread_t **thread)
{
	long i;

	i = -1;
	while (++i < (*info)->number_of_philo_and_forks)
		pthread_join((*thread)[i], NULL);
	ft_mut_destr((*info)->number_of_philo_and_forks);
	free(*thread);
}
