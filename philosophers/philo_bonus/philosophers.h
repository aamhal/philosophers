/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:41:59 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/27 07:45:33 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_Philosophers
{
	struct s_data	*d_data;
	int				id;
	int				num_eaten;
	long long		last_eat;
}t_philo;

typedef struct s_data
{
	t_philo			*p_philo;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meal;
	pid_t			*pid;
	long long		timer;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*flag;
}t_data;

//parsing
int			parsing(char **av);
t_data		*fill_struct(int ac, char **av);
void		philo_info(t_data **dt);

//philo_utils
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long long	get_current_time_ms(void);
void		ft_usleep(long long time, t_data *dt, t_philo *ph);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//philo utils 2
void		semaphore_destroy(t_data *data);
void		ft_print(t_data *data, int id, char *msg);
void		*rot(void *philo);
void		ft_free(t_data *data);
void		check_statut(pid_t *pid, int ph);

//routin
int			make_philo(t_data **dt);
void		*routine(void *philo);
void		initialisation_sem(t_data *data);

#endif