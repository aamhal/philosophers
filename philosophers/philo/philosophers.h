/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:41:59 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/23 10:14:18 by aamhal           ###   ########.fr       */
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

typedef struct s_Philosophers
{
	struct s_data	*d_data;
	pthread_t		ph;
	int				id;
	int				num_eaten;
	long long		last_eat;
	int				r_fork;
	int				l_fork;
}t_philo;

typedef struct s_data
{
	t_philo			*p_philo;
	int				f;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meal;
	int				is_dead;
	long long		timer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex;
	pthread_mutex_t	time;
	pthread_mutex_t	flag;
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
void		mutex_destroy(t_data *data);
void		ft_print(t_data *data, int id, char *msg);
void		main_th(t_data *data);
void		*rot(void *philo);
void		ft_free(t_data *data);

//routin
int			make_philo(t_data **dt);
void		*routine(void *philo);

#endif