/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/06/08 11:08:14 by lsun             ###   ########.fr       */
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
	int					num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
}						t_arg;

typedef struct s_philo
{
	int					num;
	int					must_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	start;
	unsigned long long	previous_meal;
	unsigned long long	last_meal;
	int					thread_id;
	int					meal_count;
	int					is_alive;
	pthread_mutex_t		*mutex_left;
	pthread_mutex_t		*mutex_right;
	pthread_mutex_t		*mutex_status;
}						t_philo;

/*
** main.c
*/
int						philo_in_threads(int argc, char **argv, t_arg *arg);
void					init_mutex(pthread_mutex_t *mutex_forks,
							pthread_mutex_t *mutex_status, int philo_num);
void					destory_mutex(pthread_mutex_t *mutex_forks,
							pthread_mutex_t *mutex_status, int philo_num);
void					philo_assignment(t_philo *ph, t_arg *arg,
							pthread_mutex_t *mutex_forks,
							pthread_mutex_t *mutex_status);
/*
** parsing.c
*/
int						parsing(int argc, char **argv, t_arg *arg);
void					*vital_monitor(void *arg);
int						init_threads(t_philo *ph);
void					*philo_routine(void *arg);

/*
** philo_utils.c
*/
unsigned long long		timestamp(unsigned long long start);
unsigned long long		get_current_time(void);
int						ft_usleep(unsigned long long microseconds, t_philo *ph, int flag);
int						update_status(t_philo *ph);
int						check_status(t_philo *ph);

#endif
