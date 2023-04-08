/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/04/08 16:14:25 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arg
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
}					t_arg;

typedef struct s_philo
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

	int				thread_id;
	int				meal_count;
	int				is_alive;
	int				status;

	unsigned long long	previous_meal;
	unsigned long long	last_meal;
	unsigned long long	start;
	int				*fork_left;
	int				*fork_right;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
}					t_philo;

//utils

int	ft_atoi_isnum(const char *str);
unsigned long long timestamp(unsigned long long start);
void init_forks(int* forks, int philo_num);
void ft_usleep(int useconds);

//thread_function
void				*monitor(void *arg);

int					parsing(int argc, char **argv, t_arg *arg);

int init_philo(int argc, char** argv);
void philo_assignment(t_philo *ph, t_arg *arg, pthread_mutex_t *mutex_forks);
void* philo_needs_to_eat(void *arg);
void* vital_monitor(void *arg);
void death_announcement (unsigned long long time_of_death, int thread_id);
void int_mutex_forks(pthread_mutex_t *mutex_forks, int philo_num);
unsigned long long get_current_time();
#endif
