/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:32 by lsun              #+#    #+#             */
/*   Updated: 2023/06/08 18:13:26 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ate_enough(t_philo *ph)
{
	if (ph->meal_count == ph->must_eat)
	{
		pthread_mutex_lock(ph->mutex_status);
		ph->is_alive = 0;
		pthread_mutex_unlock(ph->mutex_status);
		return (-1);
	}
	return (1);
}

int	odd_wait_here(t_philo *ph)
{
	if (ph->thread_id % 2 != 0)
	{
		if (ft_usleep(ph->time_to_eat * 1000, ph, 1) == -1)
			return (-1);
	}
	return (0);
}
