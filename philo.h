/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/05/23 21:18:28 by lsun             ###   ########.fr       */
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
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	previous_meal;
	unsigned long long	last_meal;
	unsigned long long	start;
	int					must_eat;
	int					thread_id;
	int					meal_count;
	int					is_alive;
	int					status;
	pthread_mutex_t		*mutex_left;
	pthread_mutex_t		*mutex_right;
	//pthread_mutex_t		mutex_is_alive;
	//pthread_mutex_t		mutex_prev_meal;
	//pthread_mutex_t		mutex_last_meal;
	//pthread_mutex_t		mutex_meal_count;
}						t_philo;

int						ft_atoi_isnum(const char *str);
void					ft_usleep(unsigned long long mseconds, t_philo *ph);
unsigned long long		timestamp(unsigned long long start);
unsigned long long		get_current_time(void);
int						parsing(int argc, char **argv, t_arg *arg);
int						init_philo(int argc, char **argv, t_arg *arg);
void					philo_assignment(t_philo *ph, t_arg *arg,
							pthread_mutex_t *mutex_forks);
void					*philo_needs_to_eat(void *arg);
void					*vital_monitor(void *arg);
void					death_announcement(unsigned long long time_of_death,
							int thread_id, t_philo *ph);
void					init_mutex_forks(pthread_mutex_t *mutex_forks,
							int philo_num);
int						eat_philo(t_philo *ph);
int						parsing_error(t_arg *arg);
int						create(pthread_t *ph_thread, t_philo *ph,
							int philo_num);
int						join(pthread_t *ph_thread, int philo_num);
int						init_threads(t_philo *ph);
#endif
