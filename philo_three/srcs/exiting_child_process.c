/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 22:43:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/22 20:44:50 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	kill_wait_processes(pid_t **pid, long number, long left)
{
	long	i;

	i = -1;
	while (++i < number)
		kill((*pid)[i], SIGKILL);
	while (--left >= 0)
		waitpid(-1, NULL, 0);
}

int			waiting_for_processes(long count_ph, pid_t **pid)
{
	long	number;
	int		status;

	number = -1;
	while (++number < count_ph)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == ST_DEATH)
			{
				kill_wait_processes(pid, count_ph, count_ph - number);
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
