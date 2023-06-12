/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 01:06:49 by cdelicia          #+#    #+#             */
/*   Updated: 2023/06/12 08:39:53 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_TWO_H
# define _PHILO_TWO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

# define SEM_DEATH "death_semaphore"
# define SEM_WRITE "write_semaphore"
# define SEM_FORKS "forks_semaphore"
# define LOOP 1
# define ON 1
# define OFF 0
# define FOOL 2

typedef struct timeval	t_time;

int						ft_strlen(char *s);
void					ft_putnbr_fd(int n, int fd);
void					*supervisor(void *array);
int						check_death(void);
void					*philo_action(void *array);
int						check_values(int ac, char **av, int **values);
void					ft_putstr_fd(char *s, int fd);
void					print_state(char *msg, int id);
int						semaphore_init(void);

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
}						t_philo;

int						g_one_death;
int						*g_death_trigger;
sem_t					*g_death_sem;
sem_t					*g_write_sem;
sem_t					*g_forks_sem;
t_time					g_time;
int						g_philo_count;
int						g_massage;
int						g_max_times;
pthread_t				*g_sv;
pthread_t				*g_ptt;

int						philos_init(t_philo **philos, int *params, int ac);
int						supervisor_init(t_philo **philos);
int						threads_init(t_philo **philos);
int						destroy_threads(t_philo *set, int *p);

#endif
