/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/21 00:28:07 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_print(t_data *data,int id,char *msg)
{
    pthread_mutex_lock(&data->print);
    printf("%lld\t%d\t%s\n", (get_current_time_ms() - data->timer), id + 1, msg);
    if (ft_strncmp(msg, "died", 4))
        pthread_mutex_unlock(&data->print);
}

void *routine(void *philo)
{
   t_philo *ph;
    t_data *dt;

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

    while (ph->num_eaten)
    {
        // Take forks
        ph->last_eat = get_current_time_ms();
        pthread_mutex_lock(&dt->forks[ph->r_fork]);
        ft_print(dt,ph->id, "has taken a fork");
        pthread_mutex_lock(&dt->forks[ph->l_fork]);
        ft_print(dt,ph->id, "has taken a fork");

        // Eating
        ft_print(dt,ph->id, "is eating");

        ft_usleep(dt->time_eat,dt,ph);
        ph->last_eat = get_current_time_ms();
        ph->num_eaten--;
        pthread_mutex_unlock(&dt->forks[ph->r_fork]);
        pthread_mutex_unlock(&dt->forks[ph->l_fork]);

        // Sleeping
        ft_print(dt,ph->id, "is sleeping");
        ft_usleep(dt->time_sleep,dt,ph);

        // Thinking
        ft_print(dt,ph->id,"is thinking");
    }
    pthread_mutex_lock(&dt->flag);
    dt->f++;
    pthread_mutex_unlock(&dt->flag);
    return NULL;
}

int make_philo(t_data *data)
{

	int	i;
    
	i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t *) * data->num_philo);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->flag, NULL);
	pthread_mutex_init(&data->time, NULL);
    i = 0;
    while (i < data->num_philo)
	pthread_mutex_init(&data->forks[i++], NULL);
    i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->p_philo[i].ph, NULL, &routine, &data->p_philo[i]) != 0)
			return (-1);
		i++;
	}
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
    i = 0;
    while (i < data->num_philo)
    {
	    pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->flag);
	pthread_mutex_destroy(&data->time);
	return (0);
}

