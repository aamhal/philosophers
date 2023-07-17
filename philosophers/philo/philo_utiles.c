/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:27:16 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/16 23:35:58 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	size_t	result;
	int		signe;

	i = 0;
	result = 0;
	signe = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (result > 9223372036854775807 && signe == -1)
		return (0);
	else if (result > 9223372036854775807 && signe == 1)
		return (-1);
	return (result * signe);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (0);
	return (-1);
}

long long get_current_time_ms() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
}

// void ft_usleep()