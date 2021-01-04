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

void philosopher()
{

}

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

t_philosopher	*init_philo(long number, long index)
{
	t_philosopher	*philo;

	if (!(philo = (t_philosopher *)malloc(sizeof(t_philosopher))))
		ft_putendl_plus_exit(MALLOC, 2);
	philo->number = index + 1;
	if (index == 0)
		philo->left_fork = number;
	else
		philo->left_fork = index;
	philo->right_fork = index + 1;
	return (philo);
}

t_args	**init_args(long number)
{
	pthread_mutex_t	*mut;
	long 			index;
	t_args			**args;

	index = -1;
	if (!(mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number)))
		ft_putendl_plus_exit(MALLOC, 2);
	while (++index < number)
		if (pthread_mutex_init(&mut[index], NULL))
			ft_putendl_plus_exit(MUTEX_INIT, 2);
	index = -1;
	if (!(args = (t_args **)malloc(sizeof(t_args *) * number)))
		ft_putendl_plus_exit(MALLOC, 2);
	while (++index < number)
	{
		if (!(args[index] = (t_args *)malloc(sizeof(t_args))))
			ft_putendl_plus_exit(MALLOC, 2);
		args[index]->philo = init_philo(number, index);
		args[index]->mut = &mut;
	}
	return (args);
}

int	main(int argc, char *argv[])
{
	t_params		*info;
	t_timepad		*time;
//	pthread_t 		*thread;
	t_args			**args;

	if (argc == 5 || argc == 6)
//
//	(void)argv;
//	char **array;
//	array = malloc(sizeof(char *) * 6);
//	array[0] = "2";
//	array[1] = "2";
//	array[2] = "34";
//	array[3] = "34";
//	array[4] = "34";
//	array[5] = "34";
//
//	if (argc == 1)
	{
		info = init_params(argv);
		args = init_args(info->number_of_philo_and_forks);
		time = start_time();
//		printf("%li\n", time->timestamp);

		long i = -1;
		while (++i < info->number_of_philo_and_forks)
		{
			printf("%li\n", args[i]->philo->number);
			printf("%li\n", args[i]->philo->left_fork);
			printf("%li\n\n", args[i]->philo->right_fork);
		}
//		sleep(5);
		time_stop(&time);
//		printf("%li\n", time->timestamp);


		/*
		 * check parser
		 */
//		printf("%li\n", info->number_of_philo_and_forks);
//		printf("%li\n", info->time_to_die);
//		printf("%li\n", info->time_to_eat);
//		printf("%li\n", info->time_to_sleep);
//		if (argc == 6)
//			printf("%li\n", info->number_of_times_each_philo_must_eat);

		/*
		 *
		 */
		ft_free(&info, &time, &args);
	}
	else
		ft_putendl_plus_exit(NUM_OF_ARGS, 2);
	return (0);
}
