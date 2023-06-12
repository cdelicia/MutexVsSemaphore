/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:30:22 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:37:30 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		philos_init(t_philo **philos, int *args, int ac)
{
	int	i;

	i = 0;
	g_philo_count = args[0];
	if (!((*philos) = (t_philo *)malloc(sizeof(t_philo) * g_philo_count)))
		return (1);
	while (i < g_philo_count)
	{
		(*philos)[i].philo_id = i + 1;
		(*philos)[i].time_to_die = args[1];
		(*philos)[i].time_to_eat = args[2];
		(*philos)[i].time_to_sleep = args[3];
		(*philos)[i].argc = ac;
		if (ac == 6)
			(*philos)[i].num_of_times_eat = args[4];
		else
			(*philos)[i].num_of_times_eat = 0;
		i++;
	}
	if (!(g_death_trigger = (int *)malloc(sizeof(int) * (args[0] + 1))))
		return (1);
	i = 1;
	while (i <= g_philo_count)
		g_death_trigger[i++] = OFF;
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
		if (pthread_create(&(threads[i]), NULL, philo_action,
		(void *)&((*philos)[i])))
			return (1);
		(*philos)[i].thread = &(threads[i]);
		i++;
		usleep(100);
	}
	return (0);
}

int		semaphore_init(void)
{
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	g_death_sem = sem_open(SEM_DEATH, O_CREAT, 0644, 1);
	g_write_sem = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	g_forks_sem = sem_open(SEM_FORKS, O_CREAT, 0644, g_philo_count);
	if (g_death_sem == NULL || g_write_sem == NULL || g_forks_sem == NULL)
		return (1);
	return (0);
}
