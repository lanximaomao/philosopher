/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:55:47 by lsun              #+#    #+#             */
/*   Updated: 2023/03/26 19:29:26 by linlinsun        ###   ########.fr       */
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

int* init_forks(t_philo *ph)
{
	int i;
	int* forks;

	forks = malloc(sizeof(int) * (ph->num + 1));//free
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
	t_philo *phs;
	struct timeval before;
	struct timeval	after;

	phs = (t_philo*)arg;
	gettimeofday(&before, NULL);
	while (1)
	{
		gettimeofday(&after, NULL);
		// how to calculate time until last meal??
		if (phs->last_meal == 1 && phs->is_eating == 0)
		{
			scheduler((void*)phs); // ask for forks
			printf("philo %d has taken a fork.\n", phs->thread_id);
		}
		if (phs->is_eating == 1)
			printf("philo %d is eating.\n", phs->thread_id);
		else if (phs->is_thinking == 1)
			printf("philo %d is thinking.\n", phs->thread_id);
		else if (phs->is_sleeping == 1)
			printf("philo %d is sleeping.\n", phs->thread_id);
		// die
		if (phs->is_alive == 0)
		{
			printf("philo %d died.\n", phs->thread_id);
			return(NULL);
		}
	}
	return (0);
}

void* scheduler(void *arg)
{
	t_philo *phs;

	phs = (t_philo*)arg;
	if(phs->thread_id == phs->num + 1)
		printf("hello from scheduler %d.\n", phs->thread_id);
	else if(phs->thread_id % 2 == 0 )
		printf("I am philo %d and I can eat first.\n", phs->thread_id);
	else if(phs->thread_id % 2 != 0 )
		printf("I am philo %d and I need to wait.\n", phs->thread_id);
	return (NULL);
}

int init_threads(t_philo *phs)
{
	int i;
	pthread_t philo[phs->num + 1];

	i = 0;
	while (i < phs->num + 1)
	{
		if (i < phs->num && pthread_create(&philo[i], NULL, &philo_needs_to_eat, (void*)(phs)) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		else if (i == phs->num && pthread_create(&philo[i], NULL, &scheduler, (void*)(phs)) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		i++;
		phs++;
	}
	i = 0;
	while (i < phs->num + 1)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			printf("error in joining threads.");
			return(0);
		}
		i++;
	}
	return(1);
}

int main(int argc, char** argv)
{
	int i;
	t_philo *ph;
	t_philo *phs;

	ph = malloc(sizeof(t_philo) * 1); //free
	if (!ph)
		return (1);
	if (parsing(ph, --argc, ++argv) == 0 )
		return (2);
	printf("philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nmust_eat = %d\n\n\n", ph->num, ph->time_to_die, ph->time_to_eat, ph->time_to_sleep, ph->must_eat);
	// creating multiple philos
	phs = malloc(sizeof(t_philo) * (ph->num + 1));
	philo_init(ph, phs);
	//creating multiple threads
	if (init_threads(phs) == 0)
		return (3);
	return(0);
}
