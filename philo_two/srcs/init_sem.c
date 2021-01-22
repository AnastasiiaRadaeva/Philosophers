/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/22 22:53:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	destroy_sem(char *print, char *check, char *forks)
{
	if (print)
	{
		sem_close(g_print);
		sem_unlink(S_PRINT);
	}
	if (check)
	{
		sem_close(g_check_time);
		sem_unlink(S_CHECK_TIME);
	}
	if (forks)
	{
		sem_close(g_forks);
		sem_unlink(S_FORKS);
	}
}

int			ft_sem_init(long number)
{
	sem_unlink(S_PRINT);
	if ((g_print = sem_open(S_PRINT, O_CREAT, O_RDWR, 1)) == SEM_FAILED)
		return ((int)(ft_putendl_plus_error(SEMAPHORE_INIT, -1, (void *)1)));
	sem_unlink(S_CHECK_TIME);
	if ((g_check_time = sem_open(S_CHECK_TIME, O_CREAT, O_RDWR, 1)) ==
																SEM_FAILED)
	{
		destroy_sem(S_PRINT, NULL, NULL);
		return ((int)(ft_putendl_plus_error(SEMAPHORE_INIT, -1, (void *)1)));
	}
	sem_unlink(S_FORKS);
	if ((g_forks = sem_open(S_FORKS, O_CREAT, O_RDWR, number)) == SEM_FAILED)
	{
		destroy_sem(S_PRINT, S_CHECK_TIME, NULL);
		return ((int)(ft_putendl_plus_error(SEMAPHORE_INIT, -1, (void *)1)));
	}
	sem_unlink(S_TWO_FORKS);
	if ((g_two_forks = sem_open(S_TWO_FORKS, O_CREAT, O_RDWR, number)) ==
																SEM_FAILED)
	{
		destroy_sem(S_PRINT, S_CHECK_TIME, S_FORKS);
		return ((int)(ft_putendl_plus_error(SEMAPHORE_INIT, -1, (void *)1)));
	}
	return (0);
}
