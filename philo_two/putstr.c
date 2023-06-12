/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:47:59 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:37:55 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

int		ft_counter(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

int		ft_power(int n)
{
	int p;

	p = 1;
	while (n > 1)
	{
		p = p * 10;
		n--;
	}
	return (p);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;
	char			c;
	int				bit;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n < 0)
		un = -n;
	else
		un = n;
	bit = ft_power(ft_counter(un));
	while (bit != 0)
	{
		c = un / bit + '0';
		ft_putchar_fd(c, fd);
		un = un % bit;
		bit = bit / 10;
	}
}
