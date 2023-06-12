/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:28:23 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:37:58 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*supervisor(void *array)
{
	unsigned int	temp;
	t_philo			*philo;

	philo = (t_philo *)array;
	temp = philo->time_to_die;
	while (--temp > 0)
	{
		sem_wait(g_death_sem);
		if (g_death_trigger[philo->philo_id] == ON)
		{
			g_death_trigger[philo->philo_id] = OFF;
			temp = philo->time_to_die;
		}
		sem_post(g_death_sem);
		if (!temp)
			break ;
		msleep(1);
	}
	if (check_death())
	{
		print_state(" died\n", philo->philo_id);
		g_one_death = ON;
	}
	return (NULL);
}

void	*philo_action(void *array)
{
	t_philo	*philo;

	philo = (t_philo*)array;
	while (LOOP)
	{
		sem_wait(g_forks_sem);
		print_state(" has taken a fork\n", philo->philo_id);
		sem_wait(g_forks_sem);
		print_state(" has taken a fork\n", philo->philo_id);
		sem_wait(g_death_sem);
		g_death_trigger[philo->philo_id] = ON;
		sem_post(g_death_sem);
		print_state(" is eating\n", philo->philo_id);
		msleep(philo->time_to_eat);
		sem_post(g_forks_sem);
		sem_post(g_forks_sem);
		philo->num_of_times_eat -= 1;
		if (philo->argc == 6 && philo->num_of_times_eat == 0)
			break ;
		print_state(" is sleeping\n", philo->philo_id);
		msleep(philo->time_to_sleep);
		print_state(" is thinking\n", philo->philo_id);
	}
	g_death_trigger[philo->philo_id] = FOOL;
	return (NULL);
}
