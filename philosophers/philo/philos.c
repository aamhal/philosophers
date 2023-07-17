/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:33:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/17 00:21:00 by aamhal           ###   ########.fr       */
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
        dt->timer = get_current_time_ms();
    if ((ph->id + 1) % 2 == 0)
        usleep(200);

        while (1)
    {
        // Take forks
        pthread_mutex_lock(&dt->forks);
        printf("%lld\t%d\thas taken the forks\n", (get_current_time_ms() - dt->timer), ph->id + 1);

        // Eating
        printf("%lld\t%d\tis eating\n", (get_current_time_ms() - dt->timer), ph->id + 1);
        usleep(dt->time_eat * 1000);
        dt->num_meal--;
        ph->last_eat = get_current_time_ms() - dt->timer;
        if (ph->last_eat >= dt->time_die)
        {
            printf("%d is dead\n", ph->id + 1);
            exit(1);
        }
        if (dt->num_meal == 0)
        {
            printf("%d----done\n", dt->p_philo->id + 1);
            return NULL;
        }

        // Release forks
        pthread_mutex_unlock(&dt->forks);

        // Sleeping
        printf("%lld\t%d\tis sleeping\n", (get_current_time_ms() - dt->timer), ph->id + 1);
        usleep(dt->time_sleep * 1000);

        // Thinking
        printf("%lld\t%d\tis thinking\n", (get_current_time_ms() - dt->timer), ph->id + 1);
    }

    return NULL;
}

int make_philo(t_data *data)
{

	int	i;
	i = 0;
	pthread_mutex_init(&data->forks, NULL);
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
	pthread_mutex_destroy(&data->forks);
	return (0);
}

