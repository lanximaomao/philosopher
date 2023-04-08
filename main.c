/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:55:47 by lsun              #+#    #+#             */
/*   Updated: 2023/04/08 19:29:48 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
allowed function:
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

/*
** EAT--> THINK --> SLEEP
*/

/*
gcc main.c ft_atoi.c  ft_itoa.c  ft_strlen.c ft_strncmp.c  ft_digit_num.c
*/

#include "philo.h"

int	init_threads(t_philo *ph)
{
	int			i;
	int			philo_num;
	pthread_t	ph_thread[ph[0].num + 1];

	philo_num = ph[0].num;
	if (pthread_create(&ph_thread[0], NULL, &vital_monitor, (void *)(ph)) != 0)
	{
		printf("error in creating threads.\n");
		return (0);
	}
	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&ph_thread[i + 1], NULL, &philo_needs_to_eat,
				(void *)(&ph[i])) != 0)
		{
			printf("error in creating threads.\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < philo_num + 1)
	{
		if (pthread_join(ph_thread[i], NULL) != 0)
		{
			printf("error in joining threads.\n");
			return (0);
		}
		i++;
	}
	return (1);
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
	int_mutex_forks(mutex_forks, arg->num);
	philo_assignment(ph, arg, mutex_forks);
	if (init_threads(ph) == 0)
		return (0);
	free(mutex_forks);
	free(ph);
	return (1);
}

void	int_mutex_forks(pthread_mutex_t *mutex_forks, int philo_num)
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

int	parsing(int argc, char **argv, t_arg *arg)
{
	arg->num = ft_atoi_isnum(argv[0]);
	arg->time_to_die = ft_atoi_isnum(argv[1]);
	arg->time_to_eat = ft_atoi_isnum(argv[2]);
	arg->time_to_sleep = ft_atoi_isnum(argv[3]);
	if (argc == 5)
	{
		arg->must_eat = ft_atoi_isnum(argv[4]);
		if (arg->must_eat == 0)
			printf("Must eat is zero. I am good, no more eating. Thanks!\n");
		else if (arg->must_eat < 0)
			printf("Must eat should be a unsigned int.\n");
		if (arg->must_eat <= 0)
			return (0);
	}
	else
		arg->must_eat = 2147483647;
	if (parsing_error(arg) == 0)
		return (0);
	if (argc == 4)
		arg->must_eat = 2147483647;
	return (1);
}

int	parsing_error(t_arg *arg)
{
	if (arg->num <= 0 || arg->time_to_die <= 0 || arg->time_to_eat < 0
		|| arg->time_to_sleep < 0)
	{
		if (arg->num == 0)
			printf("Are you sure to start the game without any philos?\n");
		if (arg->time_to_die == 0)
			printf("Time to die is zero. Very sad, I died immediately.\n");
		else
			printf("wrong input.\n");
		return (0);
	}
	return (1);
}

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
