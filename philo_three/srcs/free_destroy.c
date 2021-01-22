/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:11:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:59:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	free_time(t_args **args)
{
	if (args && *args && (*args)->time)
	{
		if ((*args)->time->t_start)
			free((*args)->time->t_start);
		if ((*args)->time->current_t)
			free((*args)->time->current_t);
		if ((*args)->time->t_zone)
			free((*args)->time->t_zone);
		free((*args)->time);
	}
}

static void	free_global(void)
{
//	if (g_print)
//		free(g_print);
//	if (g_check_time)
//		free(g_check_time);
//	if (g_forks)
//		free(g_forks);
//	if (g_two_fork)
//		free(g_two_fork);
	if (g_time_to_die)
	{
		if (g_time_to_die->t_zone)
			free(g_time_to_die->t_zone);
		if (g_time_to_die->current_t)
			free(g_time_to_die->current_t);
		if (g_time_to_die->t_start)
			free(g_time_to_die->t_start);
		free(g_time_to_die);
	}
}

int			ft_free(t_params ***info, t_args **args, pid_t **pid, int ret)
{
	free_time(args);
	if (info && *info && **info)
	{
		free(**info);
		free(*info);
	}
	if (args && *args)
		free(*args);
	if (pid && *pid)
		free(*pid);
	free_global();
	return (ret);
}

void		ft_sem_destr(void)
{
//	sem_post(g_print);
	sem_close(g_print);
	sem_unlink(S_PRINT);
//	sem_post(g_check_time);
	sem_close(g_check_time);
	sem_unlink(S_CHECK_TIME);
//	sem_post(g_forks);
	sem_close(g_forks);
	sem_unlink(S_FORKS);
//	sem_post(g_two_fork);
	sem_close(g_two_fork);
	sem_unlink(S_TWO_FORKS);
}
