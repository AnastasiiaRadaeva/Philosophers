/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:51:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				g_error = 0;
int				g_close = 0;
int				*g_number_of_meals = NULL;
pthread_mutex_t	*g_print = NULL;
t_timepad		**g_time_to_die = NULL;
pthread_mutex_t **g_fork = NULL;
pthread_mutex_t *g_w = NULL;

int				main(int argc, char *argv[])
{
	t_params	**info;
	pthread_t	*thread;
	t_args		**args;

	info = NULL;
	args = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!(info = init_params(argv, argc)))
			return (0);
		if (initialization(info, &args, &thread))
			return (ft_free(&info, &args, 0));
		if (create_threads(info, args, &thread))
			return (ft_free(&info, &args, 0));
		check_term_conditions(args, info, argc, 0);
		waiting_for_threads(info, &thread);
	}
	else
		ft_putendl_plus_error(NUM_OF_ARGS, -1, 0);
	return (ft_free(&info, &args, 0));
}
