/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:38:58 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/23 03:07:10 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->flag);
	pthread_mutex_destroy(&data->time);
}

void	ft_print(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print);
	printf("%lld\t%d\t%s\n", (get_current_time_ms() - data->timer), id + 1, msg);
	if (ft_strncmp(msg, "died", 4))
		pthread_mutex_unlock(&data->print);
}

void	main_th(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->is_dead)
			break ;
		pthread_mutex_unlock(&data->mutex);
		pthread_mutex_lock(&data->flag);
		if (data->f == data->num_philo)
		{
			pthread_mutex_unlock(&data->flag);
			break ;
		}
		pthread_mutex_unlock(&data->flag);
	}
}

void	*rot(void *philo)
{
	t_philo	*ph;
	t_data	*dt;

	ph = (t_philo *)philo;
	dt = ph->d_data;
	pthread_mutex_lock(&dt->forks[ph->r_fork]);
	ft_print(dt, ph->id, "has taken a fork");
	if (dt->num_philo == 1)
	{
		ft_usleep(dt->time_die, dt, ph);
		ft_usleep(dt->time_die, dt, ph);
	}
	pthread_mutex_lock(&dt->forks[ph->l_fork]);
	ft_print(dt, ph->id, "has taken a fork");
	ft_print(dt, ph->id, "is eating");
	ft_usleep(dt->time_eat, dt, ph);
	ph->last_eat = get_current_time_ms();
	ph->num_eaten--;
	pthread_mutex_unlock(&dt->forks[ph->r_fork]);
	pthread_mutex_unlock(&dt->forks[ph->l_fork]);
	ft_print(dt, ph->id, "is sleeping");
	ft_usleep(dt->time_sleep, dt, ph);
	ft_print(dt, ph->id, "is thinking");
	return (NULL);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->num_meal)
	{
		free(&data->p_philo->ph[i]);
		free(&data->p_philo[i]);
		free(&data->forks[i]);
	}
	free(data);
}
