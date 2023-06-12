/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:28:23 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:38:32 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*supervisor(void *array)
{
	unsigned int	temp;
	t_philo			*philo;

	philo = (t_philo *)array;
	temp = philo->time_to_die;
	while (--temp > 0)
	{
		pthread_mutex_lock(&(philo->check_death_mutex));
		if (g_death_trigger[philo->philo_id] == ON)
		{
			g_death_trigger[philo->philo_id] = OFF;
			temp = philo->time_to_die;
		}
		pthread_mutex_unlock(&(philo->check_death_mutex));
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

void	*philo(void *array)
{
	t_philo	*philo;

	philo = (t_philo*)array;
	while (LOOP)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(" has taken a fork\n", philo->philo_id);
		pthread_mutex_lock(philo->right_fork);
		print_state(" has taken a fork\n", philo->philo_id);
		pthread_mutex_lock(&(philo->check_death_mutex));
		g_death_trigger[philo->philo_id] = ON;
		pthread_mutex_unlock(&(philo->check_death_mutex));
		print_state(" is eating\n", philo->philo_id);
		msleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
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
