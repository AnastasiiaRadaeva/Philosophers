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

int				g_error = 0;
int				g_close = 0;
pthread_mutex_t	*g_print = NULL;
t_timepad		**g_time_to_die = NULL;

t_params	*init_params(char **args, int argc)
{
	t_params	*info;

	if (!(info = (t_params *)malloc(sizeof(t_params))))
	{
		ft_putendl_plus_error(MALLOC, -1);
		return (NULL);
	}
	info->number_of_philo_and_forks = ft_atoi(args[1], 1);
	info->time_to_die = ft_atoi(args[2], 0);
	info->time_to_eat = ft_atoi(args[3], 0);
	info->time_to_sleep = ft_atoi(args[4], 0);
	if (argc == 6)
		info->number_of_times_each_philo_must_eat = ft_atoi(args[5], 3);
	return (info);
}

t_philosopher	*init_philo(long number, long index)
{
	t_philosopher	*philo;

	if (!(philo = (t_philosopher *)malloc(sizeof(t_philosopher))))
	{
		ft_putendl_plus_error(MALLOC, -1);
		return (NULL);
	}
	philo->number = index + 1;
	if (index == 0)
		philo->left_fork = number;
	else
		philo->left_fork = index;
	philo->right_fork = index + 1;
	philo->state = sleeping;
	return (philo);
}

t_args	**init_args(long number, t_params **info, t_timepad **time)
{
	pthread_mutex_t	*mut;
	long 			index;
	t_args			**args;


	index = -1;
	if (number < 1)
		return (NULL);
	if (!(mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number)))
	{
		ft_putendl_plus_error(MALLOC, -1);
		return (NULL);
	}
	while (++index < number)
		if (pthread_mutex_init(&mut[index], NULL))
		{
			ft_putendl_plus_error(MUTEX_INIT, -1);
			free(mut);
			return (NULL);
		}
	index = -1;
	if (!(args = (t_args **)malloc(sizeof(t_args *) * number)))
	{
		ft_putendl_plus_error(MALLOC, -1);
		return (NULL);
	}
	while (++index < number)
	{
		if (!(args[index] = (t_args *)malloc(sizeof(t_args))))
		{
			ft_putendl_plus_error(MALLOC, -1);
			return (NULL);
		}
		args[index]->philo = init_philo(number, index);
		args[index]->mut = &mut;
		args[index]->info = info;
		args[index]->time = time;
	}
	return (args);
}

int	main(int argc, char *argv[])
{
	t_params		*info;
	t_timepad		*time;
	pthread_t 		*thread;
	t_args			**args;
	long 			i;

	info = NULL;
	time = NULL;
	args = NULL;
//	if (argc == 5 || argc == 6)

	(void)argv;
	char **array;
	array = malloc(sizeof(char *) * 6);
	array[0] = "2";
	array[1] = "3";
	array[2] = "5000";
	array[3] = "100";
	array[4] = "200";
	array[5] = "34";

	if (argc == 1)
	{
		info = init_params(array, 5);
		if (!(g_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
			ft_putendl_plus_error(MALLOC, -1);

		if (!(g_time_to_die = (t_timepad **)malloc(sizeof(t_timepad *) * info->number_of_philo_and_forks)))
			ft_putendl_plus_error(MALLOC, -1);
		i = -1;
		while (++i < info->number_of_philo_and_forks)
		{
			if (!(g_time_to_die[i] = start_time()))
				return (ft_free(&info, &time, &args, 0));
			gettimeofday(g_time_to_die[i]->current_t, g_time_to_die[i]->t_zone);
		}
		if (!(thread = (pthread_t *)malloc((sizeof(pthread_t) * info->number_of_philo_and_forks))))
			ft_putendl_plus_error(MALLOC, -1);
		time = start_time();
		args = init_args(info->number_of_philo_and_forks, &info, &time);
		if (pthread_mutex_init(g_print, NULL))
			ft_putendl_plus_error(MUTEX_INIT, -1);
		if (g_error == -1)
			return (ft_free(&info, &time, &args, 0));
		i = -1;
		while (++i < info->number_of_philo_and_forks)
			if (pthread_create(&thread[i], NULL, philosopher, args[i]))
				return (ft_free(&info, &time, &args, 0));

		i = 0;
		while (g_time_to_die[i]->timestamp < info->time_to_die) //добавить условие про количество раз, когда философы едят
		{
			if (i == info->number_of_philo_and_forks - 1)
				i = 0;
			else
				i++;
//			i = (i == (info->number_of_philo_and_forks - 1) ? 0 : i++);
			time_stop(&g_time_to_die[i]);
		}
		pthread_mutex_lock(g_print);
		g_close = 1;
		print_state(args[i]->philo->number, &time, DEATH);
		pthread_mutex_unlock(g_print);

		i = -1;
		while (++i < info->number_of_philo_and_forks)
			pthread_join(thread[i], NULL);
		i = -1;
		while (++i < info->number_of_philo_and_forks)
			pthread_mutex_destroy(&(*(args[0]->mut))[i]);
		pthread_mutex_destroy(g_print);
	}
	else
		ft_putendl_plus_error(NUM_OF_ARGS, -1);
	return (ft_free(&info, &time, &args, 0));
}
