/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/15 23:33:40 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void *routine(void *philo)
{

	t_philo *ph;
	t_data *dt;

	ph = (t_philo *)philo;
	dt = ph->d_data;
	if (ph->id == 0)
		dt->timer  = get_current_time_ms();
	printf("%d\n",dt->time_eat);
	if (dt->p_philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		printf("%lld %d is eating\n",(get_current_time_ms() - dt->timer) ,dt->p_philo->id);
	}	
	return NULL;
}

int make_philo(t_data *data)
{

	int	i;
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->p_philo[i].ph, NULL, &routine, &data->p_philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (data->num_philo > i)
	{
		if (pthread_join(data->p_philo[i].ph, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

