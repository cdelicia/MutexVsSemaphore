/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 01:02:00 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:38:08 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_values(int ac, char **av, int **values)
{
	int i;
	int j;

	if (!(*values = (int *)malloc(sizeof(int) * ac)))
		return (1);
	i = 1;
	j = 0;
	while (i < ac)
		(*values)[j++] = atoi(av[i++]);
	if (j > 3 && ((*values)[0] < 2 || (*values)[1] < 1 ||
	(*values)[2] < 1 || (*values)[3] < 1))
	{
		ft_putstr_fd("Wrong parameters\n", 1);
		return (1);
	}
	if (ac == 6)
	{
		if ((*values)[4] < 0)
			return (1);
		g_max_times = (*values)[4];
	}
	return (0);
}

int		check_death(void)
{
	int	i;

	i = 1;
	while (i <= g_philo_count)
		if (g_death_trigger[i++] != FOOL)
			return (1);
	if (g_massage == OFF)
	{
		ft_putstr_fd("\nAll of them have already eaten ", 1);
		ft_putnbr_fd(g_max_times, 1);
		ft_putstr_fd(" times\n", 1);
		g_massage = ON;
	}
	return (0);
}
