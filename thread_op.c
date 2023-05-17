/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:56:51 by lsun              #+#    #+#             */
/*   Updated: 2023/04/11 10:18:32 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_philo *ph)
{
	int			philo_num;
	pthread_t	*ph_thread;

	philo_num = ph[0].num;
	ph_thread = malloc(sizeof(pthread_t) * (philo_num + 1));
	if (!ph_thread)
	{
		printf("malloc fail.\n");
		return (0);
	}
	if (create(ph_thread, ph, philo_num) == 0)
		return (0);
	if (join(ph_thread, philo_num) == 0)
		return (0);
	free(ph_thread);
	return (1);
}

int	create(pthread_t *ph_thread, t_philo *ph, int philo_num)
{
	int	i;

	i = 0;
	if (pthread_create(&ph_thread[0], NULL, &vital_monitor, (void *)(ph)) != 0)
	{
		printf("error in creating threads.\n");
		return (0);
	}
	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&ph_thread[i + 1], NULL, &philo_needs_to_eat,
				(void *)(&ph[i])) != 0)
		{
			printf("error in creating threads.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	join(pthread_t *ph_thread, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num + 1)
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
