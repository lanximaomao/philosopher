/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:55:47 by lsun              #+#    #+#             */
/*   Updated: 2023/03/31 13:47:20 by linlinsun        ###   ########.fr       */
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

void init_forks(int* forks, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		forks[i] = 0;
		//printf("my fork condition is %d\n", forks[i]);
		i++;
	}
}

int init_threads(t_philo *ph)
{
	int i;
	int philo_num;
	pthread_t ph_thread[ph[0].num + 1];

	philo_num =  ph[0].num;
	if (pthread_create(&ph_thread[0], NULL, &vital_monitor, (void*)(ph)) != 0)
	{
		printf("error in creating threads.\n");
		return(0);
	}
	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&ph_thread[i + 1], NULL, &philo_needs_to_eat, (void*)(&ph[i])) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		i++;
	}
	i = 0;
	while (i < philo_num + 1) // join also the monitoring thread
	{
		if (pthread_join(ph_thread[i], NULL) != 0)
		{
			printf("error in joining threads.\n");
			return(0);
		}
		i++;
	}
	return(1);
}

int init_philo(int argc, char** argv)
{
	t_arg	*arg;
	t_philo *ph;
	int* forks;
	pthread_mutex_t *mutex_forks;

	arg = malloc(sizeof(t_arg) *  1); // remember to free
	if (!arg)
		return (0);
	if (parsing(argc, argv, arg) == 0)
		return (0);
	if (arg->num == 1)
	{
		usleep(arg->time_to_die);
		return (-1);
	}
	ph = malloc(sizeof(t_philo) * arg->num); // remember to free
	if (!ph)
		return (0);
	mutex_forks = malloc(sizeof(pthread_mutex_t) * arg->num); // TO BE FREE
	if (!mutex_forks)
		return (0);
	forks = malloc(sizeof(int) * arg->num);
	if (!forks)
		return(0);
	init_forks(forks, arg->num);
	int_mutex_forks(mutex_forks, arg->num);
	philo_assignment(ph, arg, forks, mutex_forks);
	//printf("\n\nphilo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nmust_eat = %d\n\n\n", arg->num, arg->time_to_die, arg->time_to_eat, arg->time_to_sleep, arg->must_eat);
	free(arg);
	if (init_threads(ph) == 0)
		return (0);
	return(1);
}

void int_mutex_forks(pthread_mutex_t *mutex_forks, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		i++;
	}
}

void philo_assignment(t_philo *ph, t_arg *arg, int* forks, pthread_mutex_t *mutex_forks)
{
	int i;

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
		ph[i].fork_left = &forks[(i+1) % arg->num];
		//printf("my left fork address  = %p\n", ph[i].fork_left);
		ph[i].fork_right = &forks[i];
		ph[i].start = get_current_time();
		ph[i].last_meal = ph[i].start;
		ph[i].previous_meal = ph[i].start;
		//printf("my right fork address = %p\n", ph[i].fork_right);
		i++;
	}
}

int parsing(int argc, char** argv, t_arg *arg)
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
		arg->must_eat = -1;
	if (arg->num <= 0 || arg->time_to_die <= 0 || arg->time_to_eat < 0 || arg->time_to_sleep < 0)
	{
		if (arg->num == 0)
			printf("Are you sure to start the game without any philos?\n");
		if (arg->time_to_die == 0)
			printf("Time to die is zero. Very sad, I died immediately.\n");
		else
			printf("wrong input.\n");
		return (0);
	}
	if (argc == 4)
		arg->must_eat = -1;
	return(1);
}

int main(int argc, char** argv)
{
	int ret;

	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments.\n");
		return (0);
	}
	ret = init_philo(--argc, ++argv);
	if (ret == 0)
		printf("something goes wrong.\n");
	if (ret == -1)
		printf("0 philo 1 died\n");
	return(0);
}
