/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/11 08:33:14 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philo_info(t_philo *philo, int index)
{
	philo->id++;
}

void *routine()
{
	return NULL;
}

int make_philo(t_data *data, t_philo *philo)
{
	int	index;

	philo->id = 0;
	philo->ph = malloc(sizeof(philo) * data->num_philo);
	index = 0;
	while (data->num_philo > index)
	{

		philo_info(philo, index);
		if (pthread_create(&philo->ph[index], NULL, &routine, NULL) != 0)
			return (-1);
		index++;
	}
	index = 0;
	while (data->num_philo > index)
	{
		if (pthread_join(philo->ph[index], NULL) != 0)
			return (-1);
		index++;
	}
	return (0);
}