/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:59:33 by lsun              #+#    #+#             */
/*   Updated: 2023/05/24 15:44:57 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_needs_to_eat(void *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = (t_philo *)arg;
	if (ph->thread_id % 2 != 0)
		ft_usleep(ph->time_to_eat, ph);
	while (ph->meal_count < ph->must_eat)
	{
		//if (ph->is_alive != 1)
		//	break ;
		printf("%llu %d is thinking\n", timestamp(ph->start), ph->thread_id);
		if (eat_philo(ph) == 0)
			return (NULL);
		if (ph->is_alive != 1)
			break ;
		printf("%llu %d is sleeping\n", timestamp(ph->start), ph->thread_id);
		if (ft_usleep(ph->time_to_sleep * 1000, ph) == 0)//someone died
			break;
		ph->meal_count++;
		if (ph->meal_count == ph->must_eat)
			break ;
	}
	return (NULL);
}

int	eat_philo(t_philo *ph)
{
	pthread_mutex_lock(ph->mutex_left);
	printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
	pthread_mutex_lock(ph->mutex_right);
	printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
	//if (ph->is_alive == 1)
	//{
		printf("%llu %d is eating\n", timestamp(ph->start), ph->thread_id);
		ph->previous_meal = ph->last_meal;
		ph->last_meal = get_current_time();
		if (ft_usleep(ph->time_to_eat * 1000, ph) == 0)
			return (0);
	//}
	//else
	//	return (0);
	pthread_mutex_unlock(ph->mutex_right);
	pthread_mutex_unlock(ph->mutex_left);
	return (1);
}

void	death_announcement(unsigned long long time_of_death, int thread_id,
		t_philo *ph)
{
	int	i;

	i = -1;
	//lock
	printf("%llu %d died\n", time_of_death, thread_id);
	//unlock
	while (++i < ph[0].num)
		ph[i].is_alive = 0;
}

void	*vital_monitor(void *arg)
{
	int		i;
	int		count;
	t_philo	*ph;

	i = 0;
	count = 0;
	ph = (t_philo *)arg;
	ft_usleep(ph[0].time_to_die * 1000, ph);
	while (1)
	{
		if (ph[i].last_meal - ph[i].previous_meal >= ph[i].time_to_die)
		{
			ph->is_alive = 0;
			break ;
		}
		if (ph[i].meal_count == ph[i].must_eat && ++count)
		{
			if (count == ph[i].num)
				return (NULL);
		}
		if (++i >= ph[0].num)
			i = 0;
	}
	death_announcement(timestamp(ph[i].start), ph[i].thread_id, ph);
	return (NULL);
}
