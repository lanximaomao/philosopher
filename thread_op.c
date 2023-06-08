/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:56:51 by lsun              #+#    #+#             */
/*   Updated: 2023/06/08 12:55:05 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create(pthread_t *ph_thread, t_philo *ph, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&ph_thread[i], NULL, &philo_routine,
				(void *)(&ph[i])) != 0)
		{
			printf("error in creating threads.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	join(pthread_t *ph_thread, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_join(ph_thread[i], NULL) != 0)
		{
			printf("error in joining threads.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static void	death(unsigned long long time_of_death, int thread_id, t_philo *ph)
{
	int	i;

	i = 0;
	printf("%llu %d died\n", time_of_death, thread_id);
	while (i < ph[0].num)
	{
		if (ph[i].thread_id != thread_id)
		{
			pthread_mutex_lock(ph[i].mutex_status);
			ph[i].is_alive = -1;
			pthread_mutex_unlock(ph[i].mutex_status);
		}
		i++;
	}
}

static int	monitor(t_philo *ph, int philo_num)
{
	int	i;
	int	count;
	int	status;

	i = 0;
	count = 0;
	while (1)
	{
		//pthread_mutex_lock(ph[i].mutex_status);
		//status = ph[i].is_alive;
		//pthread_mutex_unlock(ph[i].mutex_status);
		pthread_mutex_lock(ph->mutex_status);
		status = update_status(&(ph[i]));
		pthread_mutex_unlock(ph->mutex_status);
		if (status == -1)
			break ;
		if (status == 0)
		{
			if (++count == ph[i].num)
				return (1);
		}
		i++;
		if (i == philo_num)
			i = 0;
	}
	death(timestamp(ph[i].start), ph[i].thread_id, ph);
	return (-1);
}

int	thread_op(t_philo *ph)
{
	int			philo_num;
	pthread_t	*ph_thread;

	philo_num = ph[0].num;
	ph_thread = malloc(sizeof(pthread_t) * philo_num);
	if (!ph_thread)
	{
		printf("malloc fail.\n");
		return (0);
	}
	if (create(ph_thread, ph, philo_num) == 0)
		return (0);
	monitor(ph, philo_num);
	if (join(ph_thread, philo_num) == 0)
		return (0);
	free(ph_thread);
	return (1);
}
