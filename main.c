/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:03:22 by lsun              #+#    #+#             */
/*   Updated: 2023/05/24 15:55:31 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** EAT--> THINK --> SLEEP
*/

#include "philo.h"

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
	ret = init_philo(--argc, ++argv, arg);
	if (ret == 0)
		printf("something goes wrong.\n");
	if (ret == -1)
		printf("0 philo 1 died\n");
	free(arg);
	return (0);
}

int	init_philo(int argc, char **argv, t_arg *arg)
{
	t_philo			*ph;
	pthread_mutex_t	*mutex_forks;

	if (parsing(argc, argv, arg) == 0)
		return (0);
	if (arg->num == 1)
	{
		usleep(arg->time_to_die * 1000);
		return (-1);
	}
	ph = malloc(sizeof(t_philo) * arg->num);
	if (!ph)
		return (0);
	mutex_forks = malloc(sizeof(pthread_mutex_t) * arg->num);
	if (!mutex_forks)
		return (0);
	init_mutex_forks(mutex_forks, arg->num);
	philo_assignment(ph, arg, mutex_forks);
	if (init_threads(ph) == 0)
		return (0);
	free(mutex_forks);
	free(ph);
	return (1);
}

void	init_mutex_forks(pthread_mutex_t *mutex_forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		i++;
	}
}

void	philo_assignment(t_philo *ph, t_arg *arg, pthread_mutex_t *mutex_forks)
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
		ph[i].status = 0;
		ph[i].start = get_current_time();
		ph[i].last_meal = ph[i].start;
		ph[i].previous_meal = ph[i].start;
		i++;
	}
}
