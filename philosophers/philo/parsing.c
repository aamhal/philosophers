/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:57 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/11 08:52:04 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(char **av)
{
	char *str;
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		str = av[i];
		j = 0;
		while(str[j])
		{
			if (ft_isdigit(str[j]) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_struct(int ac, char **av, t_data *data)
{
	data->num_philo =ft_atoi(av[1]);
	data->time_die =ft_atoi(av[2]);
	data->time_eat =ft_atoi(av[3]);
	data->time_sleep =ft_atoi(av[4]);
	if (ac == 6)
		data->num_meal = ft_atoi(av[5]);
	else
		data->num_meal = 0;
}