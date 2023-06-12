/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:30:22 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:38:12 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		philos_init(t_philo **philos, int *params, int argc)
{
	int	i;

	i = 0;
	g_philo_count = params[0];
	if (!((*philos) = (t_philo *)malloc(sizeof(t_philo) * g_philo_count)))
		return (1);
	while (i < g_philo_count)
	{
		(*philos)[i].philo_id = i + 1;
		(*philos)[i].time_to_die = params[1];
		(*philos)[i].time_to_eat = params[2];
		(*philos)[i].time_to_sleep = params[3];
		(*philos)[i].argc = argc;
		if (argc == 6)
			(*philos)[i].num_of_times_eat = params[4];
		else
			(*philos)[i].num_of_times_eat = 0;
		i++;
	}
	if (!(g_death_trigger = (int *)malloc(sizeof(int) * (params[0] + 1))))
		return (1);
	i = 1;
	while (i <= g_philo_count)
		g_death_trigger[i++] = 0;
	return (0);
}

int		supervisor_init(t_philo **philos)
{
	int			i;
	pthread_t	*svs;

	i = 0;
	if (!(svs = (pthread_t *)malloc(sizeof(pthread_t) * g_philo_count)))
		return (1);
	g_sv = svs;
	while (i < g_philo_count)
	{
		if (pthread_create(&(svs[i]), NULL, supervisor,
		(void *)&((*philos)[i])))
			return (1);
		(*philos)[i].supervisor = &(svs[i]);
		usleep(40);
		i++;
	}
	return (0);
}

int		threads_init(t_philo **philos)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) *
	g_philo_count)))
		return (1);
	g_ptt = threads;
	while (i < g_philo_count)
	{
		if (pthread_create(&(threads[i]), NULL, philo,
		(void *)&((*philos)[i])))
			return (1);
		(*philos)[i].thread = &(threads[i]);
		i++;
		usleep(100);
	}
	return (0);
}

int		mutexes_init(t_philo **philos)
{
	int				i;
	pthread_mutex_t *mutex;

	i = 0;
	if (!(mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
	g_philo_count)))
		return (1);
	g_mtx = mutex;
	while (i < g_philo_count)
	{
		pthread_mutex_init(&((*philos)[i]).check_death_mutex, NULL);
		pthread_mutex_init(&mutex[i++], NULL);
	}
	i = 0;
	while (i < g_philo_count)
	{
		(*philos)[i].left_fork = &(mutex[i]);
		if ((*philos)[i].philo_id == g_philo_count)
			(*philos)[i].right_fork = &(mutex[0]);
		else
			(*philos)[i].right_fork = &(mutex[i + 1]);
		i++;
	}
	pthread_mutex_init(&g_print_mutex, NULL);
	return (0);
}
