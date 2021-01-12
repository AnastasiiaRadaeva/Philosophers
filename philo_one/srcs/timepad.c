/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timepad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:55:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/12/28 19:34:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_timepad	*start_time(void)
{
	t_timepad	*time;

	if(!(time = (t_timepad *)malloc(sizeof(t_timepad))))
		return ((t_timepad *)ft_putendl_plus_error(MALLOC, -1, NULL));
	if(!(time->t_start = (struct timeval *)malloc(sizeof(struct timeval))))
		return ((t_timepad *)ft_putendl_plus_error(MALLOC, -1, NULL));
	if(!(time->current_t = (struct timeval *)malloc(sizeof(struct timeval))))
		return ((t_timepad *)ft_putendl_plus_error(MALLOC, -1, NULL));
	time->timestamp = 0;
	if(!(time->t_zone = (struct timezone *)malloc(sizeof(struct timezone))))
		return ((t_timepad *)ft_putendl_plus_error(MALLOC, -1, NULL));
	gettimeofday(time->t_start, time->t_zone);
	return (time);
}

void	*time_stop(t_timepad **time, long *timestamp)
{
	struct timeval	*difference;

	gettimeofday((*time)->current_t, (*time)->t_zone);
	if (!(difference = (struct timeval *)malloc(sizeof(struct timeval))))
		return (ft_putendl_plus_error(MALLOC, -1, NULL));
	difference->tv_sec = (*time)->current_t->tv_sec - (*time)->t_start->tv_sec;
	difference->tv_usec = (*time)->current_t->tv_usec - (*time)->t_start->tv_usec;
	if(difference->tv_usec < 0)
	{
		difference->tv_sec--;
		difference->tv_usec += 1000000;
	}
	*timestamp = difference->tv_sec * 1000 + difference->tv_usec / 1000;
	(*time)->timestamp = *timestamp;
	free(difference);
	return (NULL);
}

