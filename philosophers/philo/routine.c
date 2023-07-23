/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:04:04 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/23 03:01:40 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philo)
{
	t_philo	*ph;
	t_data	*dt;

	ph = (t_philo *)philo;
	dt = ph->d_data;
	if (ph->id == 0)
	{
		pthread_mutex_lock(&dt->time);
		dt->timer = get_current_time_ms();
		pthread_mutex_unlock(&dt->time);
	}
	if ((ph->id) % 2 != 0)
		usleep(200);
	ph->last_eat = get_current_time_ms();
	while (ph->num_eaten)
	{
		rot(ph);
	}
	pthread_mutex_lock(&dt->flag);
	dt->f++;
	pthread_mutex_unlock(&dt->flag);
	return (NULL);
}

int	make_philo(t_data **dt)
{
	t_data	*data;
	int		i;

	data = *dt;
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t *) * data->num_philo);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->flag, NULL);
	pthread_mutex_init(&data->time, NULL);
	while (i++ < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->num_philo)
	{	
		if (pthread_create(&data->p_philo[i].ph, NULL, \
		&routine, &data->p_philo[i]) != 0)
			return (-1);
		i++;
	}
	main_th(data);
	mutex_destroy(data);
	return (0);
}
