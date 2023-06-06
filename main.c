/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:03:22 by lsun              #+#    #+#             */
/*   Updated: 2023/06/06 23:18:47 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** to be fixed: ./philo 3 410 200 200 100
** destory mutex
*/

int	main(int argc, char **argv)
{
	int		ret;
	t_arg	*arg;

	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments.\n");
		return (0);
	}
	arg = malloc(sizeof(t_arg) * 1);
	if (!arg)
		return (0);
	ret = philo_in_threads(--argc, ++argv, arg);
	if (ret == -1)
		printf("0 philo 1 died\n");
	free(arg);
	return (0);
}

int	philo_in_threads(int argc, char **argv, t_arg *arg)
{
	t_philo			*ph;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	*mutex_status;

	if (parsing(argc, argv, arg) == 0)
		return (0);
	if (arg->num == 1)
	{
		usleep(arg->time_to_die * 1000);
		return (-1);
	}
	ph = malloc(sizeof(t_philo) * arg->num);
	mutex_forks = malloc(sizeof(pthread_mutex_t) * arg->num);
	mutex_status = malloc(sizeof(pthread_mutex_t) * arg->num);
	if (!ph || !mutex_forks || !mutex_status)
		return (0);
	init_mutex(mutex_forks, mutex_status, arg->num);
	philo_assignment(ph, arg, mutex_forks, mutex_status);
	if (init_threads(ph) == 0)
		return (0);
	destory_mutex(mutex_forks, mutex_status, arg->num);
	free(mutex_status);
	free(mutex_forks);
	free(ph);
	return (1);
}

void	init_mutex(pthread_mutex_t *mutex_forks, pthread_mutex_t *mutex_status,
		int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		pthread_mutex_init(&mutex_status[i], NULL);
		i++;
	}
}

void	philo_assignment(t_philo *ph, t_arg *arg, pthread_mutex_t *mutex_forks,
		pthread_mutex_t *mutex_status)
{
	int	i;

	i = 0;
	while (i < arg->num)
	{
		ph[i].num = arg->num;
		ph[i].time_to_die = arg->time_to_die;
		ph[i].time_to_eat = arg->time_to_eat;
		ph[i].time_to_sleep = arg->time_to_sleep;
		ph[i].must_eat = arg->must_eat;
		ph[i].thread_id = i + 1;
		ph[i].mutex_left = &mutex_forks[(i + 1) % arg->num];
		ph[i].mutex_right = &mutex_forks[i];
		ph[i].meal_count = 0;
		ph[i].is_alive = 1;
		ph[i].start = get_current_time();
		ph[i].start_meal = ph[i].start;
		ph[i].previous_meal = ph[i].start;
		ph[i].mutex_status = &mutex_status[i];
		i++;
	}
}

void	destory_mutex(pthread_mutex_t *mutex_forks,
		pthread_mutex_t *mutex_status, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_destroy(&mutex_forks[i]);
		pthread_mutex_destroy(&mutex_status[i]);
		i++;
	}
}
