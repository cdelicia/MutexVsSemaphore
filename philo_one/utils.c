/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:30:57 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:38:37 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

void	msleep(t_mseconds time_limit)
{
	t_time		tv;
	t_mseconds	time_start;
	t_mseconds	current_time;

	gettimeofday(&tv, NULL);
	time_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	current_time = time_start;
	while (current_time - time_start < time_limit)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}

void	print_state(char *massage, int philo_id)
{
	t_time tval;

	gettimeofday(&tval, NULL);
	pthread_mutex_lock(&g_print_mutex);
	if (g_one_death != ON)
	{
		ft_putnbr_fd((tval.tv_sec - g_time.tv_sec) * 1000 +
		(tval.tv_usec - g_time.tv_usec) / 1000, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(philo_id, 1);
		ft_putstr_fd(massage, 1);
	}
	pthread_mutex_unlock(&g_print_mutex);
}

int		destroy_threads(t_philo *set, int *params)
{
	int i;

	i = 0;
	if (set)
	{
		pthread_mutex_destroy(&g_print_mutex);
		while (i < g_philo_count)
		{
			pthread_mutex_destroy(&set[i].check_death_mutex);
			pthread_mutex_destroy(set[i].left_fork);
			i++;
		}
		free(g_death_trigger);
		free(g_sv);
		free(g_ptt);
		free(g_mtx);
		free(set);
		free(params);
	}
	return (1);
}
