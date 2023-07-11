/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pholosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:32:44 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/11 08:32:48 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>

typedef struct s_data
{
	struct s_Philosophers *philo;
	int	num_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int num_meal;
	int	*forks;
}t_data;

typedef struct s_Philosophers
{
	struct s_data *data;
	pthread_t *ph;
	int id;
	int num_eaten;
	int last_eat;
}t_philo;

//parsing
int	parsing(char **av);
void	fill_struct(int ac, char **av, t_data *data);

//philo_utiles
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

//philo
int make_philo(t_data *data, t_philo *philo);
void philo_info(t_philo *philo, int index);
void *routine();


#endif