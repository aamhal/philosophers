/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:27:22 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/25 07:07:09 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		printf("wrong arguments\n");
		return (1);
	}
	if (parsing(av) == -1)
	{
		printf("bad arguments\n");
		return (1);
	}
	data = fill_struct(ac, av);
	philo_info(&data);
	if (make_philo( &data) == -1)
		return (1);
	ft_free(data);
	return (0);
}
