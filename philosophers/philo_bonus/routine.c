/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:04:04 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/27 07:45:29 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philo)
{
	t_philo	*ph;
	t_data	*dt;

	ph = (t_philo *)philo;
	dt = ph->d_data;
	ph->last_eat = get_current_time_ms();
	while (ph->num_eaten)
	{
		rot(ph);
	}
	exit(0);
}

void	initialisation_sem(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("flag");
	data->forks = sem_open("forks", O_CREAT, 777, data->num_philo);
	data->print = sem_open("print", O_CREAT, 777, 1);
	data->flag = sem_open("flag", O_CREAT, 777, 1);
}

int	make_philo(t_data **dt)
{
	t_data	*data;
	int		i;

	data = *dt;
	initialisation_sem(data);
	i = 0;
	data->pid = malloc(sizeof(pid_t) * (data->num_philo + 1));
	data->pid[data->num_philo] = 0;
	data->timer = get_current_time_ms();
	while (i < data->num_philo)
	{
		data->pid[i] = fork();
		if (!data->pid[i])
		{
			routine(&data->p_philo[i]);
		}
		i++;
	}
	check_statut(data->pid, data->num_philo);
	return (0);
}
