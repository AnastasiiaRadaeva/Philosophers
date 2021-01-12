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

void	*ft_putendl_plus_error(char *str, int flag, void *ret)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	g_error = flag;
	return (ret);
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
		return ((long)ft_putendl_plus_error(WRONG_RANGE, -1, (void *)-1));
	if (str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		n = (n * 10 + (str[index] - '0'));
		if (n > 2147483647)
			return ((long)ft_putendl_plus_error(WRONG_RANGE, -1, (void *)-1));
		else if ((n > 200 || n < 2) && flag == 1)
			return ((long)ft_putendl_plus_error(NUM_OF_PH, -1, (void *)-1));
		index++;
	}
	if (index != ft_strlen(str))
		return ((long)ft_putendl_plus_error(WRONG_FORMAT, -1, (void *)-1));
	return ((flag == 1 || flag == 3) ? n : n * 1000);
}

int ft_free(t_params ***info, t_args ***args, int ret)
{
	if (args && *args && (*args)[0] && *((*args)[0]->mut))
	{
		free(*((*args)[0]->mut));
		free(&(*((*args)[0]->mut)));
	}
	if (args && *args && (*args)[0] && *((*args)[0]->time))
	{
		if ((*((*args)[0]->time))->t_start)
			free((*((*args)[0]->time))->t_start);
		if ((*((*args)[0]->time))->current_t)
			free((*((*args)[0]->time))->current_t);
		if ((*((*args)[0]->time))->t_zone)
			free((*((*args)[0]->time))->t_zone);
		free(*((*args)[0]->time));
		free(&(*((*args)[0]->time)));
	}
	if (info && *info)
		while (--(**info)->number_of_philo_and_forks >= 0)
		{
			if ((*args)[(**info)->number_of_philo_and_forks]->philo)
				free((*args)[(**info)->number_of_philo_and_forks]->philo);
			if ((*args)[(**info)->number_of_philo_and_forks])
				free((*args)[(**info)->number_of_philo_and_forks]);
			if (g_time_to_die[(**info)->number_of_philo_and_forks])
			{
				if (g_time_to_die[(**info)->number_of_philo_and_forks]->t_zone)
					free(g_time_to_die[(**info)->number_of_philo_and_forks]->t_zone);
				if (g_time_to_die[(**info)->number_of_philo_and_forks]->current_t)
					free(g_time_to_die[(**info)->number_of_philo_and_forks]->current_t);
				if (g_time_to_die[(**info)->number_of_philo_and_forks]->t_start)
					free(g_time_to_die[(**info)->number_of_philo_and_forks]->t_start);
				free(g_time_to_die[(**info)->number_of_philo_and_forks]);
			}
		}
	if (args && *args)
		free(*args);
//	if (g_time_to_die)
//		free(g_time_to_die);
	if (info && *info && **info)
	{
		free(**info);
		free(*info);
	}
//	if (g_number_of_meals)
//		free(g_number_of_meals);
//	if (g_print)
//		free(g_print);
	return (ret);
}

void ft_mut_destr(long number, t_args *args)
{
	long i;

	i = -1;
	while (++i < number)
		pthread_mutex_destroy(&(*(args->mut))[i]);
	pthread_mutex_destroy(g_print);
}

long		ft_g_init(long number)
{
	long	i;

	i = -1;
	if(!(g_number_of_meals = (int *)malloc(sizeof(int) * number)))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	while (++i < number)
		g_number_of_meals[i] = 0;
	if (!(g_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t))))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	if (!(g_time_to_die = (t_timepad **)malloc(sizeof(t_timepad *) * number)))
		return ((long)ft_putendl_plus_error(MALLOC, -1, (void *)1));
	i = -1;
	while (++i < number)
		if (!(g_time_to_die[i] = start_time()))
			return (1);
	return (0);
}

