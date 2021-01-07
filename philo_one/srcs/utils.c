/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2020/12/28 19:34:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_strlen(const char *s)
{
	int len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	ft_putendl_plus_error(char *str, int flag)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	g_error = flag;
}

long	ft_atoi(char *str, int flag)
{
	int			index;
	long long	n;

	index = 0;
	n = 0;
	while ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-')
	{
		ft_putendl_plus_error(WRONG_RANGE, -1);
		index++;
	}
	if (str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		n = (n * 10 + (str[index] - '0'));
		if (n > 2147483647)
			ft_putendl_plus_error(WRONG_RANGE, -1);
		else if ((n > 200 || n < 2) && flag == 1)
			ft_putendl_plus_error(NUM_OF_PH, -1);
		index++;
	}
	if (index != ft_strlen(str))
		ft_putendl_plus_error(WRONG_FORMAT, -1);
	return ((flag == 1 || flag == 3) ? n : n * 1000);
}

int ft_free(t_params **info, t_timepad **time, t_args ***args, int ret)
{
	if (*args && (*args)[0] && *((*args)[0]->mut))
		free(*((*args)[0]->mut));
	if (*info)
		while (--(*info)->number_of_philo_and_forks >= 0)
		{
			if ((*args)[(*info)->number_of_philo_and_forks]->philo)
				free((*args)[(*info)->number_of_philo_and_forks]->philo);
			if ((*args)[(*info)->number_of_philo_and_forks])
				free((*args)[(*info)->number_of_philo_and_forks]);
		}
	if (*args)
		free(*args);
	if (*info)
		free(*info);
	if (*time)
	{
		if ((*time)->t_start)
			free((*time)->t_start);
		if ((*time)->current_t)
			free((*time)->current_t);
		if ((*time)->t_zone)
			free((*time)->t_zone);
		free(*time);
	}
	return (ret);
}

