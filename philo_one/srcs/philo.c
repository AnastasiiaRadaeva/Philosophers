/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/12/28 19:34:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_params	*init_params(char **args)
{
	t_params	*info;

	if (!(info = (t_params *)malloc(sizeof(t_params))))
		ft_putendl_plus_exit(MALLOC, 2);
	info->number_of_philo_and_forks = ft_atoi(args[1], 1);
	info->time_to_die = ft_atoi(args[2], 0);
	info->time_to_eat = ft_atoi(args[3], 0);
	info->time_to_sleep = ft_atoi(args[4], 0);
	if (args[5])
		info->number_of_times_each_philo_must_eat = ft_atoi(args[5], 0);
	return (info);
}

int	main(int argc, char *argv[])
{
	t_params	*info;
	t_timepad	*time;

	if (argc == 5 || argc == 6)
	{
		info = init_params(argv);
		time = start_time();
		printf("%li\n", time->timestamp);
		sleep(5);
		time_stop(&time);
		printf("%li\n", time->timestamp);


		/*
		 * check parser
		 */
		printf("%li\n", info->number_of_philo_and_forks);
		printf("%li\n", info->time_to_die);
		printf("%li\n", info->time_to_eat);
		printf("%li\n", info->time_to_sleep);
		if (argc == 6)
			printf("%li\n", info->number_of_times_each_philo_must_eat);

		/*
		 *
		 */
	}
	else
		ft_putendl_plus_exit(NUM_OF_ARGS, 2);
	return (0);
}
