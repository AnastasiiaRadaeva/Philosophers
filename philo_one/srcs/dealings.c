/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:17:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/12/28 19:34:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

//каждому дейсвию поставить сообщение и сделать глобальную переменную, которая не даст сразу всем процессам печатать свое состояние.

void	ft_thinking(t_philosopher **philo, t_params *info)
{
	(*philo)->state = thinking;

}

void	ft_sleeping(t_philosopher **philo, t_params *info)
{
	(*philo)->state = sleeping;
	usleep(info->time_to_sleep);
}

void	ft_eating(t_philosopher **philo, t_params *info)
{
	(*philo)->state = eating;
	usleep(info->time_to_eat);
}

