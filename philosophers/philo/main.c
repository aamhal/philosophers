/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:27:22 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/21 00:38:31 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_free(t_data *data)
{
	int i;
	i = 0;
	while (i++ < data->num_philo)
	{
		free(&data->forks[i]);
		free(&data->p_philo[i]);
	}
	free(&data->forks);
	free(&data->p_philo);
	free(&data);
}
void v()
{
	system("leaks philo");
}
int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("wrong arguments\n");
		return (1);
	}
	if (parsing(av) == -1)
	{
		printf("bad arguments\n");
		return (1);
	}
	t_data data;
	
	fill_struct(ac, av, &data);
	atexit(v);
	return (0);
}