/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:27:22 by aamhal            #+#    #+#             */
/*   Updated: 2023/07/17 22:24:41 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
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
	t_data data;
	
	fill_struct(ac, av, &data);
	return (0);
}