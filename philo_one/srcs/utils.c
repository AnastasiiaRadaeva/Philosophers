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

void ft_putendl_plus_exit(char *str, int flag)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (flag == 0)
		exit(EXIT_SUCCESS);
	if (flag == 1)
		exit(EXIT_FAILURE);
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
		ft_putendl_plus_exit(WRONG_RANGE, 0);
	if (str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		n = (n * 10 + (str[index] - '0'));
		if (n > 2147483647)
			ft_putendl_plus_exit(WRONG_RANGE, 0);
		else if ((n > 200 || n == 0) && flag == 1)
			ft_putendl_plus_exit(NUM_OF_PH, 0);
		index++;
	}
	if (index != ft_strlen(str))
		ft_putendl_plus_exit(WRONG_FORMAT, 0);
	return (n);
}
