
#include "philo.h"


void* philo_needs_to_eat(void *arg)
{
	t_philo *ph;
	struct timeval before;

	ph = (t_philo*)arg;
	gettimeofday(&before, NULL);
	if (ph->thread_id % 2 != 0)
		usleep(50);
	while (ph->meal_count == -1 || ph->meal_count < ph->must_eat)
	{
		printf("%lu %d is thinking\n", timestamp(before), ph->thread_id);
		pthread_mutex_lock(ph->mutex_left);
		*(ph->fork_left) = ph->thread_id;
		printf("%lu %d has taken a fork\n", timestamp(before), ph->thread_id);
		pthread_mutex_lock(ph->mutex_right);
		*(ph->fork_right) = ph->thread_id;
		printf("%lu %d has taken a fork\n", timestamp(before), ph->thread_id);
		printf("%lu %d is eating\n", timestamp(before), ph->thread_id);
		usleep(ph->time_to_eat * 1000);
		*(ph->fork_right) = 0;
		*(ph->fork_left) = 0;
		pthread_mutex_unlock(ph->mutex_right);
		pthread_mutex_unlock(ph->mutex_left);
		printf("%lu %d is sleeping\n", timestamp(before), ph->thread_id);
		usleep(ph->time_to_sleep * 1000);
		if (ph->must_eat != -1)
			ph->meal_count++;
	}
	return (NULL);
}

void* monitor(void *arg)
{
	t_philo *ph;

	ph = (t_philo*)arg;
	printf("hello from monitor.\n");
	return(NULL);
}

