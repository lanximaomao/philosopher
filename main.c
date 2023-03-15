/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:55:47 by lsun              #+#    #+#             */
/*   Updated: 2023/03/15 22:58:42 by linlinsun        ###   ########.fr       */
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

void* func(void* forks)
{
	printf("Is my fork available? Fork is %d.\n", *((int*)forks));
	return (NULL);
}

int is_unsigned_int(char* str)
{
	if (ft_strncmp(str, ft_itoa(ft_atoi(str)), ft_strlen(str)) == 0 && ft_atoi(str) > 0)
		return(1);
	else
		return(0);
}

int parsing(t_philo *ph, int argc, char** argv)
{
	int i;

	argv++;
	if (is_unsigned_int(argv[0]) == 0 || is_unsigned_int(argv[1]) == 0 || is_unsigned_int(argv[0]) == 0 || is_unsigned_int(argv[1]) == 0)
	{
		printf("not a number. \n");
		return (0);
	}
	if (argc == 6 && is_unsigned_int(argv[0]) == 0)
		return (0);
	ph->num = ft_atoi(argv[0]);
	ph->time_to_die = ft_atoi(argv[1]);
	ph->time_to_eat = ft_atoi(argv[2]);
	ph->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 6)
		ph->must_eat = ft_atoi(argv[4]);
	else
		ph->must_eat = 1000;
	return(1);
}

int init_threads(t_philo *ph, int *forks)
{
	int i;
	pthread_t each_philo[ph->num];

	i = 0;
	while (i < ph->num)
	{
		if(pthread_create(&each_philo[i], NULL, &func, &forks[i]) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		i++;
	}
	i = 0;
	while (i < ph->num)
	{
		if (pthread_join(each_philo[i], NULL) != 0)
		{
			printf("error in joining threads.\n");
			return(0);
		}
		i++;
	}
	return(1);
}

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

int main(int argc, char** argv)
{
	int i;
	int * forks;
	t_philo *ph;

	// parsing
	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments.\n");
		return (0);
	}
	ph = malloc(sizeof(t_philo) * 1);
	if (!ph)
		return(1);
	if (parsing(ph, argc, argv) == 0 )
	{
		printf("wrong input.\n");
		return (2);
	}
	//creating multiple threads
	forks = init_forks(ph);
	if (!forks)
		return(0);
	if (init_threads(ph, forks) == 0)
		return (3);
	return(0);
}
