/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 14:26:42 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:39:47 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_ONE_H
# define _PHILO_ONE_H
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define LOOP 1
# define ON 1
# define OFF 0
# define FOOL 2

int						ft_strlen(char *s);
void					ft_putnbr_fd(int n, int fd);
void					*supervisor(void *arr);
int						check_death(void);
void					*philo(void *arr);
int						check_values(int ac, char **av, int **values);
void					ft_putstr_fd(char *s, int fd);
void					print_state(char *phrase, int phil_num);

typedef struct timeval	t_time;

int						g_one_death;
int						*g_death_trigger;
t_time					g_time;
pthread_mutex_t			g_print_mutex;
int						g_max_times;
int						g_massage;
pthread_t				*g_sv;
pthread_t				*g_ptt;
pthread_mutex_t			*g_mtx;
int						g_philo_count;

typedef	unsigned int	t_mseconds;
void					msleep(t_mseconds time);

typedef struct			s_philo
{
	int					philo_id;
	int					argc;
	int					num_of_times_eat;
	t_mseconds			time_to_die;
	t_mseconds			time_to_eat;
	t_mseconds			time_to_sleep;
	pthread_t			*supervisor;
	pthread_t			*thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		check_death_mutex;
}						t_philo;

int						philos_init(t_philo **philos, int *params, int argc);
int						supervisor_init(t_philo **philos);
int						threads_init(t_philo **philos);
int						mutexes_init(t_philo **philos);
int						destroy_threads(t_philo *set, int *p);

#endif
