/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:43:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:51:50 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			initialization(t_params **info, t_args **args)
{
	ft_g_init();
	*args = init_args(&info);
	ft_sem_init((*info)->number_of_philo_and_forks);
	return (0);
}

void		check_term_conditions(t_args **args, t_params **info)
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
		if (g_number_of_meals >= (*info)->number_of_times_each_philo_must_eat && (*info)->number_of_times_each_philo_must_eat != -1)
		{
			sem_wait(g_print);
			exit(ST_FED);
		}
	}
}



void kill_wait_processes(pid_t **pid, long number, long left)
{
	long i;

	i = -1;
	while (++i < number)
		kill((*pid)[i], SIGKILL);
	while (--left >= 0)
		waitpid(-1, NULL, 0);
}

int	waiting_for_processes(t_params **info, pid_t **pid)
{
	long 	number;
	int 	status;

	number = -1;
	while (++number < (*info)->number_of_philo_and_forks)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == ST_DEATH)
			{
				kill_wait_processes(pid, (*info)->number_of_philo_and_forks, (*info)->number_of_philo_and_forks - number);
				sem_post(g_print);
				return (ST_DEATH);
			}
			if (WEXITSTATUS(status) == ST_FED)
			{
				sem_post(g_print);
				continue ;
			}
		}
		else
			ft_putendl_plus_error(SIGNAL, SUCCESS);
	}
	return (ST_FED);
}
