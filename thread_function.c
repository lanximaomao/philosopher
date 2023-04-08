#include "philo.h"

void* philo_needs_to_eat(void *arg)
{
	int i;
	t_philo *ph;

	i = 0;
	ph = (t_philo*)arg;
	if (ph->thread_id % 2 != 0)
		usleep(ph->time_to_eat);
	while (ph->meal_count < ph->must_eat)
	{
		if (ph->is_alive != 1)
			break;
		printf("%llu %d is thinking\n", timestamp(ph->start), ph->thread_id);
		pthread_mutex_lock(ph->mutex_left);
		printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
		pthread_mutex_lock(ph->mutex_right);
		printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
		if (ph->is_alive == 1)
		{
			printf("%llu %d is eating\n", timestamp(ph->start), ph->thread_id);
			ph->previous_meal = ph->last_meal;
			ph->last_meal = get_current_time();
			usleep(ph->time_to_eat * 1000);
		}
		else
			return(NULL);
		pthread_mutex_unlock(ph->mutex_right);
		pthread_mutex_unlock(ph->mutex_left);
		if (ph->is_alive != 1)
			break;
		printf("%llu %d is sleeping\n", timestamp(ph->start), ph->thread_id);
		usleep(ph->time_to_sleep * 1000);
			ph->meal_count++;
		if (ph->meal_count == ph->must_eat)
			break;
	}
	return (NULL);
}

void death_announcement (unsigned long long time_of_death, int thread_id)
{
	printf("%llu %d died\n", time_of_death, thread_id);
}

void* vital_monitor(void *arg)
{
	int i;
	int j;
	int count;
	t_philo *ph;

	i = 0;
	j = 0;
	count= 0;
	ph = (t_philo*)arg;

	usleep(ph[0].time_to_die);
	while (1)
	{
		if (ph[i].last_meal - ph[i].previous_meal >= ph[i].time_to_die)
		{
			ph->is_alive = 0;
			break;
		}
		if (ph[i].meal_count == ph[i].must_eat)
		{
			count++;
			if (count == ph[i].num)
				return(NULL);
		}
		i++;
		if (i >= ph[0].num)
			i = 0;
	}
	while (j < ph[0].num)
	{
			ph[j].is_alive = 0;
		j++;
	}
	death_announcement(timestamp(ph[i].start), ph[i].thread_id);
	return(NULL);
}

