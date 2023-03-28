/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/03/28 23:54:29 by linlinsun        ###   ########.fr       */
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

	struct timeval	last_meal;

	pthread_mutex_t	left;
	pthread_mutex_t	right;
}					t_philo;

//utils

int	ft_atoi_isnum(const char *str);
long				timestamp(struct timeval before);

//thread_function
void				*monitor(void *arg);

int					parsing(int argc, char **argv, t_arg *arg);

int init_philo(int argc, char** argv);
void philo_assignment(t_philo *ph, t_arg *arg, pthread_mutex_t *mutex_forks);
void* philo_needs_to_eat(void *arg);
void* monitor(void *arg);
#endif
