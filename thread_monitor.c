/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:59:33 by lsun              #+#    #+#             */
/*   Updated: 2023/06/06 21:17:56 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	death_announcement(unsigned long long time_of_death, int thread_id,
		t_philo **ph)
{
	int	i;

	i = -1;
	printf("%llu %d died\n", time_of_death, thread_id);
	while (++i < (*ph)[0].num)
	{
		pthread_mutex_lock((*ph)[i].mutex_status);
		(*ph)[i].is_alive = -1;
		pthread_mutex_unlock((*ph)[i].mutex_status);
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
	ft_usleep(ph[0].time_to_die * 1000, &ph, 0);
	while (1)
	{
		status = check_status(&ph);
		if (status == -1)
			break ;
		if (status == 0)
		{
			count++;
			if (count == ph[i].num)
				return (NULL);
		}
		if (++i >= ph[0].num)
			i = 0;
	}
	death_announcement(timestamp(ph[i].start), ph[i].thread_id, &ph);
	return (NULL);
}
