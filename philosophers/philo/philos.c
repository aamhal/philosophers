/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/18 01:58:50 by aamhal           ###   ########.fr       */
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
        dt->timer = get_current_time_ms();
    if ((ph->id + 1) % 2 == 0)
        usleep(200);

        while (1)
    {
        // Take forks
        pthread_mutex_lock(&dt->forks[ph->r_fork]);
        ft_print(dt,ph->id, "has taken a fork");
        // printf("%d\n", ph->r_fork);
        pthread_mutex_lock(&dt->forks[ph->l_fork]);
        ft_print(dt,ph->id, "has taken a fork");
        // printf("%d\n", ph->l_fork);

        // Eating
        ft_print(dt,ph->id, "is eating");
        ft_usleep(dt->time_eat);
        pthread_mutex_unlock(&dt->forks[ph->r_fork]);
        pthread_mutex_unlock(&dt->forks[ph->l_fork]);
        pthread_mutex_lock(&dt->meals);
        dt->num_meal--;
        pthread_mutex_unlock(&dt->meals);
        ph->last_eat = get_current_time_ms() - dt->timer;
        if (ph->last_eat >= dt->time_die)
            ft_print(dt,ph->id, "died");
        int n;
        pthread_mutex_lock(&dt->meals);
        n = dt->num_meal;
        pthread_mutex_unlock(&dt->meals);
        
        if (n == 0)
            return NULL;

        // Release forks

        // Sleeping
        ft_print(dt,ph->id, "is sleeping");
        ft_usleep(dt->time_sleep);

        // Thinking
        ft_print(dt,ph->id,"is thinking");
    }

    return NULL;
}

int make_philo(t_data *data)
{

	int	i;
    
	i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t *) * data->num_philo);
    while (i < data->num_philo)
    {
	    pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meals, NULL);
    i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->p_philo[i].ph, NULL, &routine, &data->p_philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->p_philo[i].ph, NULL) != 0)
			return (-1);
		i++;
	}
    while (i < data->num_philo)
    {
	    pthread_mutex_destroy(&data->forks[i]);
            i++;
    }
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meals);
	return (0);
}

