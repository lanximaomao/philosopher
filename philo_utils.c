/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:32 by lsun              #+#    #+#             */
/*   Updated: 2023/06/08 17:13:06 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	timestamp(unsigned long long start)
{
	unsigned long long	current_time;

	current_time = get_current_time();
	return (current_time - start);
}

unsigned long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
** flag 0 means no need to do mutex
** -1 means no need to sleep, 0 means sleep the whole time
*/
int	ft_usleep(unsigned long long microseconds, t_philo *ph, int flag)
{
	int					status;
	unsigned long long	current_time;

	status = 0;
	current_time = get_current_time();
	while (timestamp(current_time) * 1000 < microseconds)
	{
		if (flag == 1)
		{
			status = update_status(ph);
			if (status == 0)
				usleep(500);
			else
				return (-1);
		}
		else
			usleep(500);
	}
	return (0);
}

int	update_status(t_philo *ph)
{
	if (timestamp(ph->last_meal) >= ph->time_to_die)
	{
		pthread_mutex_lock(ph->mutex_status);
		ph->is_alive = -1;
		pthread_mutex_unlock(ph->mutex_status);
		return (-1);
	}
	return (0);
}

int	check_status(t_philo *ph)
{
	int	status;

	pthread_mutex_lock(ph->mutex_status);
	status = ph->is_alive;
	pthread_mutex_unlock(ph->mutex_status);
	return (status);
}
