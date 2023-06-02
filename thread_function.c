/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:59:33 by lsun              #+#    #+#             */
/*   Updated: 2023/06/02 08:17:24 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = (t_philo *)arg;
	if (ph->thread_id % 2 != 0)
		usleep(ph->time_to_eat);
	while (ph->meal_count < ph->must_eat)
	{
		//if (check_status(ph) == 0)
		//	break ;
		printf("%llu %d is thinking\n", timestamp(ph->start), ph->thread_id);
		if (philo_eat(ph) == 0)
			break ;
		//if (check_status(ph) == 0)
		//	break ;
		printf("%llu %d is sleeping\n", timestamp(ph->start), ph->thread_id);
		if (ft_usleep(ph->time_to_sleep * 1000, ph, 1) == 0)
			break ;
		if (check_ate_enough(ph) != 0)
			break ;
	}
	return (NULL);
}

int check_ate_enough(t_philo *ph)
{
	int ret;

	if (ph->last_meal - ph->previous_meal >= ph->time_to_die)
	{
		ph->is_alive = 0; // is dead
		printf("%llu %d died\n", timestamp(ph->start), ph->thread_id);
		return(-1);
	}
	if (ph->meal_count == ph->must_eat)
	{
		ret = 1; // ate engouh, need to return from main thread
	}
	else
		ret = 0; // need to eat more
	//pthread_mutex_unlock(ph->mutex_left);
	return (ret);
}

int	philo_eat(t_philo *ph)
{
	//int ret;

	pthread_mutex_lock(ph->mutex_left);
	printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
	pthread_mutex_lock(ph->mutex_right);
	printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
	//if (check_status(ph) == 1)
	//{
		printf("%llu %d is eating\n", timestamp(ph->start), ph->thread_id);
		ph->previous_meal = ph->last_meal;
		ph->last_meal = get_current_time();
		if (ft_usleep(ph->time_to_eat * 1000, ph, 1) == 0)
		{
			pthread_mutex_unlock(ph->mutex_right);
			pthread_mutex_unlock(ph->mutex_left);
			return (0);
		}
	//}
	//else
	//	return (0);
	pthread_mutex_unlock(ph->mutex_right);
	pthread_mutex_unlock(ph->mutex_left);
	ph->meal_count++;
	return (1);
}

void	death_announcement(unsigned long long time_of_death, int thread_id,
		t_philo *ph)
{
	int	i;

	i = -1;
	printf("%llu %d died\n", time_of_death, thread_id);
	while (++i < ph[0].num)
	{
		//pthread_mutex_lock(ph[i].mutex_status);
		ph[i].is_alive = 0;
		//pthread_mutex_unlock(ph[i].mutex_status);
	}
}

void	*vital_monitor(void *arg)
{
	//int		i;
	//int		count;
	t_philo	*ph;

	//i = 0;
	//count = 0;
	ph = (t_philo *)arg;
	//ft_usleep(ph[0].time_to_die * 1000, ph, 0);//0 means no lock
	//while (1)
	//{
	//	//pthread_mutex_lock(ph[i].mutex_status);
	//	if (ph[i].last_meal - ph[i].previous_meal >= ph[i].time_to_die)
	//	{
	//		ph[i].is_alive = 0;
	//		break ;
	//	}
	//	if (ph[i].meal_count == ph[i].must_eat && ++count)
	//	{
	//		if (count == ph[i].num)
	//		{
	//			//pthread_mutex_unlock(ph[i].mutex_status);
	//			return (NULL);
	//		}
	//	}
	//	if (++i >= ph[0].num)
	//		i = 0;
	//}
	////pthread_mutex_unlock(ph[i].mutex_status);
	//death_announcement(timestamp(ph[i].start), ph[i].thread_id, ph);
	return (NULL);
}
