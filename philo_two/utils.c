/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:30:57 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:38:02 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

void	msleep(t_mseconds time)
{
	t_time		current_t;
	t_mseconds	start;
	t_mseconds	now;

	gettimeofday(&current_t, NULL);
	start = current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
	now = start;
	while (now - start < time)
	{
		usleep(100);
		gettimeofday(&current_t, NULL);
		now = current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
	}
}

void	print_state(char *massage, int philo_id)
{
	t_time current_t;

	gettimeofday(&current_t, NULL);
	sem_wait(g_write_sem);
	if (g_one_death != 1)
	{
		ft_putnbr_fd((int)(current_t.tv_sec - g_time.tv_sec) * 1000
		+ (current_t.tv_usec - g_time.tv_usec) / 1000, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(philo_id, 1);
		ft_putstr_fd(massage, 1);
	}
	sem_post(g_write_sem);
}

int		destroy_threads(t_philo *set, int *par)
{
	if (set)
	{
		sem_unlink(SEM_DEATH);
		sem_unlink(SEM_WRITE);
		sem_unlink(SEM_FORKS);
		if (g_death_trigger)
			free(g_death_trigger);
		if (par)
			free(par);
		if (g_sv)
			free(g_sv);
		if (g_ptt)
			free(g_ptt);
		free(set);
	}
	return (1);
}
