/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:59:33 by lsun              #+#    #+#             */
/*   Updated: 2023/06/08 17:23:10 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int philo_think(t_philo* ph)
{
	if (update_status(ph) == -1)
		return (-1);
	printf("%llu %d is thinking\n", timestamp(ph->start), ph->thread_id);
	return (0);
}

static int ate_enough(t_philo *ph)
{
	ph->meal_count++;
	if (ph->meal_count == ph->must_eat)
	{
		pthread_mutex_lock(ph->mutex_status);
		ph->is_alive = 0;
		pthread_mutex_unlock(ph->mutex_status);
		return (-1); // no need to eat
	}
	return(1);// still need to eat
}
/*
** return -1 means philo no need to eat or died
** check for status, otherwise, one can get stuck here.
*/
static int	philo_eat(t_philo *ph)
{
	if (update_status(ph) == -1)
		return (-1);
	// 3 410 200 200
	//if (ph->num % 2 != 0)
	//{
	//	if (ft_usleep(ph->time_to_eat * 1000, ph, 1) == -1)
	//		return (-1);
	//}
	pthread_mutex_lock(ph->mutex_left);
	printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
	if (check_status(ph) == -1)
		return (-1);
	pthread_mutex_lock(ph->mutex_right);
	printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
	printf("%llu %d is eating\n", timestamp(ph->start), ph->thread_id);
	ph->previous_meal = ph->last_meal;
	ph->last_meal = get_current_time();
	if (ft_usleep(ph->time_to_eat * 1000, ph, 1) == -1)
		return (-1);
	pthread_mutex_unlock(ph->mutex_right);
	pthread_mutex_unlock(ph->mutex_left);
	if (ate_enough(ph) == -1)
		return (-1);
	return (0);
}


static int	philo_sleep(t_philo *ph)
{
	int	status;

	status = check_status(ph);
	if (status == 1)
		printf("%llu %d is sleeping\n", timestamp(ph->start), ph->thread_id);
	else
		return (-1);
	if (ft_usleep(ph->time_to_sleep * 1000, ph, 1) == -1)
		return (-1);
	return (0);
}

static int	odd_wait_here(t_philo *ph)
{
	if (ph->thread_id % 2 != 0)
	{
		if (ft_usleep(ph->time_to_eat * 1000, ph, 1) == -1)
			return (-1);
	}
	return (0);
}
/*
** 0 means no need to do mutex
** first ft_usleep: need to use mutex here so that 4 110 200 200 can be handled
** last if: no don't need to wait for the fork in case of 4 410 200 100
*/

void	*philo_routine(void *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = (t_philo *)arg;
	if (odd_wait_here(ph) == -1)
		return (NULL);
	while (ph->meal_count < ph->must_eat)
	{
		if (philo_think(ph) == -1)
			return (NULL);
		if (philo_eat(ph) == -1)
			return (NULL);
		if (philo_sleep(ph) == -1)
			return (NULL);
		//case 01
		if (ph->time_to_eat > ph->time_to_sleep)
		{
			if (ft_usleep((ph->time_to_eat - ph->time_to_sleep) * 1000, ph,
					1) == -1)
				return (NULL);
		}
		//case 02
		if (ph->num % 2 != 0)
		{
			if (ft_usleep(ph->time_to_eat * 1000, ph, 1) == -1)
				return(NULL);
		}
	}
	return (NULL);
}
