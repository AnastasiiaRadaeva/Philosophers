/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:26:57 by kbatwoma          #+#    #+#             */
/*   Updated: 2021/01/17 22:55:56 by kbatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_strlen(const char *s)
{
	int	len;

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
		index++;
	}
	if ((n > 200 || n < 2) && flag == 1)
		return ((long)ft_putendl_plus_error(NUM_OF_PH, -1, (void *)-1));
	if (index != ft_strlen(str))
		return ((long)ft_putendl_plus_error(WRONG_FORMAT, -1, (void *)-1));
	return ((flag == 1 || flag == 3) ? n : n * 1000);
}
