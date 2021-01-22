/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timepad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:55:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/22 20:56:16 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_timepad	*start_time(void)
{
	t_timepad	*time;

	if (!(time = (t_timepad *)malloc(sizeof(t_timepad))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	if (!(time->t_start = (struct timeval *)malloc(sizeof(struct timeval))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	if (!(time->current_t = (struct timeval *)malloc(sizeof(struct timeval))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	time->current_t->tv_usec = 0;
	time->current_t->tv_sec = 0;
	time->timestamp = 0;
	if (!(time->t_zone = (struct timezone *)malloc(sizeof(struct timezone))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	gettimeofday(time->t_start, time->t_zone);
	return (time);
}

void		*time_stop(t_timepad **time, long *timestamp)
{
	struct timeval	*difference;

	gettimeofday((*time)->current_t, (*time)->t_zone);
	if (!(difference = (struct timeval *)malloc(sizeof(struct timeval))))
		ft_putendl_plus_error(MALLOC, FAILURE);
	difference->tv_sec = (*time)->current_t->tv_sec - (*time)->t_start->tv_sec;
	difference->tv_usec =
				(*time)->current_t->tv_usec - (*time)->t_start->tv_usec;
	*timestamp = difference->tv_sec * 1000 + difference->tv_usec / 1000;
	(*time)->timestamp = *timestamp;
	free(difference);
	return (NULL);
}
