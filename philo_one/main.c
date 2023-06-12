/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:30:39 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:38:16 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int ac, char **av)
{
	int		*params;
	t_philo	*philos_arr;

	gettimeofday(&g_time, NULL);
	g_one_death = OFF;
	g_massage = OFF;
	if (ac < 5 || ac > 6 || check_values(ac, av, &params))
	{
		ft_putstr_fd("Bad arguments! May be: 5 800 200 200 7\n", 1);
		return (1);
	}
	if (philos_init(&philos_arr, params, ac) == ON ||
	mutexes_init(&philos_arr) == ON || supervisor_init(&philos_arr) == ON
	|| threads_init(&philos_arr) == ON)
		return (destroy_threads(philos_arr, params));
	while (check_death())
		if (g_one_death == ON)
		{
			ft_putstr_fd("\nSomeone died because of the time had passed\n", 1);
			break ;
		}
	destroy_threads(philos_arr, params);
	return (0);
}
