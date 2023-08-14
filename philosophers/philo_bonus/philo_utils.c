/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:27:16 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/27 06:50:55 by aamhal           ###   ########.fr       */
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

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

void	ft_usleep(long long time, t_data *dt, t_philo *ph)
{
	long long	t;

	t = get_current_time_ms();
	while (1)
	{
		if ((get_current_time_ms() - ph->last_eat) >= dt->time_die)
		{
			ft_print(dt, ph->id, "died");
			exit(1);
		}
		if ((get_current_time_ms() - t) >= time)
			return ;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		else if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		i++;
	}
	return (0);
}
