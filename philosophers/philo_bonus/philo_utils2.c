/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:38:58 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/27 07:45:44 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	semaphore_destroy(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->flag);
}

void	ft_print(t_data *data, int id, char *msg)
{
	sem_wait(data->print);
	printf("%lld\t%d\t%s\n", (get_current_time_ms() - data->timer), id + 1, msg);
	if (ft_strncmp(msg, "died", 4))
		sem_post(data->print);
}

void	*rot(void *philo)
{
	t_philo	*ph;
	t_data	*dt;

	ph = (t_philo *)philo;
	dt = ph->d_data;
	sem_wait(dt->forks);
	ft_print(dt, ph->id, "has taken a fork");
	if (dt->num_philo == 1)
	{
		ft_usleep(dt->time_die, dt, ph);
		ft_usleep(dt->time_die, dt, ph);
	}
	sem_wait(dt->forks);
	ft_print(dt, ph->id, "has taken a fork");
	ft_print(dt, ph->id, "is eating");
	ft_usleep(dt->time_eat, dt, ph);
	ph->last_eat = get_current_time_ms();
	ph->num_eaten--;
	sem_post(dt->forks);
	sem_post(dt->forks);
	ft_print(dt, ph->id, "is sleeping");
	ft_usleep(dt->time_sleep, dt, ph);
	ft_print(dt, ph->id, "is thinking");
	return (NULL);
}

void	check_statut(pid_t *pid, int ph)
{
	int	i;
	int	status;

	if (!ph)
		return ;
	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		while (pid[i])
			kill(pid[i++], SIGKILL);
	}
	else
		check_statut(pid, ph--);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	semaphore_destroy(data);
	free(data->p_philo);
	free(data->pid);
	free(data);
}
