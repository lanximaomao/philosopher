/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/03/27 00:06:11 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
	int				is_eating;
	int				is_thinking;
	int				is_sleeping;
	struct timeval	last_meal;
	int*	forks;
	pthread_mutex_t* mutex_forks;
}					t_philo;

typedef struct s_info
{
	t_philo			*phs;
}					t_info;

int					parsing(t_philo *ph, int argc, char **argv);
int					ft_atoi(const char *str);
int				philo_init(t_philo *ph, t_philo *phs);
void				*scheduler(void *arg);
long				timestamp(struct timeval before);
void *first_meal(t_philo *phs, int* forks);
int init_forks(t_philo *ph);
int put_back_forks(t_philo *phs);
#endif
