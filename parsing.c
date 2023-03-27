/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:37:37 by lsun              #+#    #+#             */
/*   Updated: 2023/03/27 14:37:38 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parsing(t_philo *ph, int argc, char** argv)
{
	int i;

	if (argc < 4 || argc > 5)
	{
		printf("wrong number of arguments.\n");
		return (0);
	}
	ph->num = ft_atoi(argv[0]);
	ph->time_to_die = ft_atoi(argv[1]);
	ph->time_to_eat = ft_atoi(argv[2]);
	ph->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		ph->must_eat = ft_atoi(argv[4]);
	else
		ph->must_eat = 1000;
	if (ph->num > 0 && ph->time_to_die > 0 && ph->time_to_eat > 0 && ph->time_to_sleep >= 0 && ph->must_eat > 0)
		return (1);
	printf("wrong input.\n");
	return(0);
}

//int init_mutex(t_philo *ph)
//{

//	ph->mutex_forks = malloc(sizeof(pthread_mutex_t) * ph->num);
//	if (!ph->mutex_forks)
//		return(0);
//	else
//		return(1);
//}

int init_forks(t_philo *ph)
{
	int i;

	ph->forks = malloc(sizeof(int) * (ph->num));//free
	if (!ph->forks)
		return (0); // error catch
	i = 0;
	while (i < ph->num)
	{
		ph->forks[i] = ph->num + 1;
		i++;
	}
	return(1);
}

int philo_init(t_philo *ph, t_philo *phs)
{
	int i;

	i = 0;
	if (init_forks(ph) == 0)
		return (0);
	while (i < ph->num + 1)
	{
		(phs[i]).num = ph->num;
		(phs[i]).time_to_die = ph->time_to_die;
		(phs[i]).time_to_eat = ph->time_to_eat;
		(phs[i]).time_to_sleep = ph->time_to_sleep;
		(phs[i]).must_eat = ph->must_eat;
		(phs[i]).thread_id = i + 1;
		(phs[i]).meal_count = 0;
		(phs[i]).is_alive = 1;
		(phs[i]).is_eating = 0;
		(phs[i]).is_thinking = 0;
		(phs[i]).is_sleeping = 0;
		(phs[i]).forks = ph->forks;
		(phs[i]).left = 0;
		(phs[i]).right = 0;
		//(phs[i]).mutex_forks = ph->mutex_forks;
		i++;
	}
	return(1);
}
