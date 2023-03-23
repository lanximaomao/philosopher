/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:55:47 by lsun              #+#    #+#             */
/*   Updated: 2023/03/23 20:25:05 by linlinsun        ###   ########.fr       */
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
gcc main.c ft_atoi.c  ft_itoa.c  ft_strlen.c ft_strncmp.c  ft_digit_num.c
*/

#include "philo.h"

int* init_forks(t_philo *ph)
{
	int i;
	int* forks;

	forks = malloc(sizeof(int) * (ph->num + 1));
	if (!forks)
		return (NULL); // error catch
	i = 0;
	while (i < ph->num)
	{
		forks[i] = 1;
		i++;
	}
	return(forks);
}

void* philo_needs_to_eat(void *arg)
{
	int fork_left;
	int fork_right;
	t_philo *ph;


	ph = (t_philo*)arg;
	usleep(1000000); // *1000
	printf("hello from philo %d.\n", ph->thread_id);
	return (0);
}

void* scheduler(void *arg)
{
	//int* forks;
	//forks = init_forks(ph);
	//if (!forks)
	//	return(0);
	//else
	//	return(1);
	return (NULL);
}

int init_threads(t_philo *ph, int *forks)
{
	int i;
	pthread_t philo[ph->num + 1];

	i = 0;
	while (i < ph->num + 1)
	{
		if (i == ph->num && pthread_create(&philo[i], NULL, &scheduler, (void*)ph) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		else if (pthread_create(&philo[i], NULL, &philo_needs_to_eat, (void*)ph) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		ph->thread_id = i;
		i++;
	}
	i = 0;
	while (i < ph->num)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			printf("error in joining threads.\n");
			return(0);
		}
		i++;
	}
	return(1);
}

int main(int argc, char** argv)
{
	int i;
	int * forks;
	t_philo *ph;

	ph = malloc(sizeof(t_philo) * 1);
	if (!ph)
		return (1);
	if (parsing(ph, --argc, ++argv) == 0 )
		return (2);
	printf("philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nmust_eat = %d\n\n\n", ph->num, ph->time_to_die, ph->time_to_eat, ph->time_to_sleep, ph->must_eat);
	//creating multiple threads
	if (init_threads(ph, forks) == 0)
		return (3);
	return(0);
}
