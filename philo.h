/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/06/04 13:09:56 by linlinsun        ###   ########.fr       */
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

int						ft_atoi_isnum(const char *str);
int						ft_usleep(unsigned long long mseconds, t_philo *ph, int flag);
unsigned long long		timestamp(unsigned long long start);
unsigned long long		get_current_time(void);
int						parsing(int argc, char **argv, t_arg *arg);
int						philo_in_threads(int argc, char **argv, t_arg *arg);
void					philo_assignment(t_philo *ph, t_arg *arg,
							pthread_mutex_t *mutex_forks, pthread_mutex_t *mutex_status);
int						philo_routine(void *arg);
void					*vital_monitor(void *arg);
void					death_announcement(unsigned long long time_of_death,
							int thread_id, t_philo *ph);
void					init_mutex(pthread_mutex_t *mutex_forks, pthread_mutex_t *mutex_status,
							int philo_num);
int						philo_eat(t_philo *ph);
int						parsing_error(t_arg *arg);
int						create(pthread_t *ph_thread, t_philo *ph,
							int philo_num);
int						join(pthread_t *ph_thread, int philo_num);
int						check_status(t_philo *ph);
int						ft_printf(const char *str, ...);
int	init_threads(t_philo *ph);

#endif
