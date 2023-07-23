/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:57 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/23 03:01:43 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(char **av)
{
	char	*str;
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		str = av[i];
		j = 0;
		while (str[j])
		{
			if (ft_isdigit(str[j]) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

t_data	*fill_struct(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = -1;
	return (data);
}

void	philo_info(t_data **dt)
{
	t_data	*data;
	int		i;

	data = *dt;
	data->p_philo = malloc(sizeof(t_philo) * data->num_philo);
	i = 0;
	while (i < data->num_philo)
	{
		data->p_philo[i].id = i;
		data->p_philo[i].d_data = data;
		data->p_philo[i].num_eaten = data->num_meal;
		data->p_philo[i].last_eat = 0;
		data->f = 0;
		data->p_philo[i].r_fork = i;
		data->p_philo[i].l_fork = (i + 1) % data->num_philo;
		i++;
	}
}
