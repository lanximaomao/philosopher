/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:59:33 by lsun              #+#    #+#             */
/*   Updated: 2023/06/02 13:55:16 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// /philo 4 110 200 200 12 should die during eating.

void	*philo_routine(void *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = (t_philo *)arg;
	if (ph->thread_id % 2 != 0)
		ft_usleep(ph->time_to_eat, ph, 0); // 0 means no need to do mutex
	while (ph->meal_count < ph->must_eat)
	{
		printf("%llu %d is thinking\n", timestamp(ph->start), ph->thread_id);
		if (philo_eat(ph) == -1)
			break ;
		printf("%llu %d is sleeping\n", timestamp(ph->start), ph->thread_id);
		if (ft_usleep(ph->time_to_sleep * 1000, ph, 1) != 1)
			break ;
	}
	return (NULL);
}

/*
** return -1 means philo is dead
** return 0 means ate enough
** return 1 means need to eat more
*/
int check_status(t_philo *ph)
{
	if (ph->last_meal - ph->previous_meal >= ph->time_to_die)
	{
		pthread_mutex_lock(ph->mutex_status);
		ph->is_alive = -1; // is dead
		pthread_mutex_unlock(ph->mutex_status);
		//printf("%llu %d died\n", timestamp(ph->start), ph->thread_id);
		return(-1);
	}
	if (ph->meal_count == ph->must_eat)
	{
		pthread_mutex_lock(ph->mutex_status);
		ph->is_alive = 0;
		pthread_mutex_unlock(ph->mutex_status);
		return (0);
	}
	else
		return(1);
}

/* return -1 means philo no need to eat */
int	philo_eat(t_philo *ph)
{
	int status;
	int ret;

	ret = 0;
	pthread_mutex_lock(ph->mutex_status);
	status = ph->is_alive;
	pthread_mutex_unlock(ph->mutex_status);

	if (status == 1)
	{
		pthread_mutex_lock(ph->mutex_left);
		printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
		pthread_mutex_lock(ph->mutex_right);
		printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
		printf("%llu %d is eating\n", timestamp(ph->start), ph->thread_id);
		ph->previous_meal = ph->last_meal;
		ph->last_meal = get_current_time();
		if (ft_usleep(ph->time_to_eat * 1000, ph, 1) ==  -1)
			return (-1);
		ph->meal_count++;
		pthread_mutex_unlock(ph->mutex_right);
		pthread_mutex_unlock(ph->mutex_left);
	}
	return (ret);
}

void	death_announcement(unsigned long long time_of_death, int thread_id,
		t_philo *ph)
{
	int	i;

	i = -1;
	printf("%llu %d died\n", time_of_death, thread_id);
	while (++i < ph[0].num)
	{
		pthread_mutex_lock(ph[i].mutex_status);
		ph[i].is_alive = 0;
		pthread_mutex_unlock(ph[i].mutex_status);
	}
}

void	*vital_monitor(void *arg)
{
	int		i;
	int		count;
	int		status;
	t_philo	*ph;

	i = 0;
	count = 0;
	ph = (t_philo *)arg;
	ft_usleep(ph[0].time_to_die * 1000, ph, 0);//0 means no lock
	while (1)
	{
		pthread_mutex_lock(ph[i].mutex_status);
		status = ph[i].is_alive;
		pthread_mutex_unlock(ph[i].mutex_status);

		// someone died
		if (status == 0)
			break;
		if (status == 2 && ++count)
		{
			if (count == ph[i].num)
				return(NULL) ;
		}
		if (++i >= ph[0].num)
			i = 0;
	}
	death_announcement(timestamp(ph[i].start), ph[i].thread_id, ph);
	return (NULL);
}
