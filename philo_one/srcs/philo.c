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
int 			*g_number_of_meals = NULL;
pthread_mutex_t	*g_print = NULL;
t_timepad		**g_time_to_die = NULL;

t_params	**init_params(char **args, int argc)
{
	t_params	**info;

	if (!(info = (t_params **)malloc(sizeof(t_params *))))
		return ((t_params **)ft_putendl_plus_error(MALLOC, -1, NULL));
	if (!(*info = (t_params *)malloc(sizeof(t_params))))
		return ((t_params **)ft_putendl_plus_error(MALLOC, -1, NULL));
	(*info)->number_of_philo_and_forks = ft_atoi(args[1], 1);
	(*info)->time_to_die = ft_atoi(args[2], 0);
	(*info)->time_to_eat = ft_atoi(args[3], 0);
	(*info)->time_to_sleep = ft_atoi(args[4], 0);
	(*info)->number_of_times_each_philo_must_eat = 1;
	if (g_error == -1)
		return (NULL);
	if (argc == 6)
		(*info)->number_of_times_each_philo_must_eat = ft_atoi(args[5], 3);
	return (info);
}

t_philosopher	*init_philo(long number, long index)
{
	t_philosopher	*philo;

	if (!(philo = (t_philosopher *)malloc(sizeof(t_philosopher))))
		return ((t_philosopher *)ft_putendl_plus_error(MALLOC, -1, NULL));
	philo->number = index + 1;
	if (index == 0)
		philo->left_fork = number;
	else
		philo->left_fork = index;
	philo->right_fork = index + 1;
	philo->timestamp = 0;
	return (philo);
}

t_args	**init_args(long number, t_params **info)
{
	pthread_mutex_t	**mut;
	long 			index;
	t_args			**args;
	t_timepad		**time;

	index = -1;
	if (number < 1)
		return (NULL);
	if (!(time = (t_timepad **)malloc(sizeof(t_timepad *))))
		return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
	if (!(*time = start_time()))
		return (NULL);
	if (!(mut = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *))))
		return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
	if (!(*mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number)))
		return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
	while (++index < number)
		if (pthread_mutex_init(&(*mut)[index], NULL))
			return ((t_args **)ft_putendl_plus_error(MUTEX_INIT, -1, NULL));
	index = -1;
	if (!(args = (t_args **)malloc(sizeof(t_args *) * number)))
		return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
	while (++index < number)
	{
		if (!(args[index] = (t_args *)malloc(sizeof(t_args))))
			return ((t_args **)ft_putendl_plus_error(MALLOC, -1, NULL));
		args[index]->philo = init_philo(number, index);
		args[index]->mut = mut;
		args[index]->info = info;
		args[index]->time = time;
	}
	return (args);
}

int	main(int argc, char *argv[])
{
	t_params		**info;
	pthread_t 		*thread;
	t_args			**args;
	long 			i;

	info = NULL;
	args = NULL;
//	if (argc == 5 || argc == 6)
/**/
	(void)argv;
	char **array;
	array = malloc(sizeof(char *) * 6);
	array[0] = "2";
	array[1] = "3";
	array[2] = "7900";
	array[3] = "500";
	array[4] = "200";
	array[5] = "5";
	if (argc == 1)
/**/
	{
/**/	argc = 6;


		if (!(info = init_params(array, argc)))
			return (ft_free(&info, &args, 0));
/**/	free(array);
		if (ft_g_init((*info)->number_of_philo_and_forks) == 1)
			return (ft_free(&info, &args, 0));
		if (!(thread = (pthread_t *)malloc((sizeof(pthread_t) * (*info)->number_of_philo_and_forks))))
		{
			ft_putendl_plus_error(MALLOC, -1, 0);
			return (ft_free(&info, &args, 0));
		}
		if (!(args = init_args((*info)->number_of_philo_and_forks, info)))
			return (ft_free(&info, &args, 0));


		if (pthread_mutex_init(g_print, NULL))
		{
			ft_putendl_plus_error(MUTEX_INIT, -1, 0);
			return (ft_free(&info, &args, 0));
		}
		i = -1;
		while (++i < (*info)->number_of_philo_and_forks)
			if (pthread_create(&thread[i], NULL, philosopher, args[i]))
			{
				free(thread);
				ft_putendl_plus_error(PTHREAD_CR, -1, 0);
				return (ft_free(&info, &args, 0));
			}


		i = 0;
		long number_of_philo_who_ate = 0;
		while ((args[i]->philo->timestamp < (((*info)->time_to_die) / 1000)) && (number_of_philo_who_ate < (*info)->number_of_philo_and_forks))
		{
			if (i == (*info)->number_of_philo_and_forks - 1)
				i = 0;
			else
				i++;
			time_stop(&(g_time_to_die[i]), &(args[i]->philo->timestamp));
			if (argc == 6)
			{
				int c = -1;
				number_of_philo_who_ate = 0;
				while (++c < (*info)->number_of_philo_and_forks)
				{
					if (g_number_of_meals[c] == (*info)->number_of_times_each_philo_must_eat)
						number_of_philo_who_ate++;
				}
			}
		}
		pthread_mutex_lock(g_print);
		g_close = 1;
		if (number_of_philo_who_ate < (*info)->number_of_philo_and_forks)
			print_state(args[i]->philo->number, args[0]->time, DEATH);
		else
			ft_putendl_plus_error("Every philosopher has eaten enough times\n", g_error, 0);
		pthread_mutex_unlock(g_print);


		i = -1;
		while (++i < (*info)->number_of_philo_and_forks)
			pthread_join(thread[i], NULL);
		ft_mut_destr((*info)->number_of_philo_and_forks, args[0]);
		free(thread);
	}
	else
		ft_putendl_plus_error(NUM_OF_ARGS, -1, 0);
	return (ft_free(&info, &args, 0));
}
