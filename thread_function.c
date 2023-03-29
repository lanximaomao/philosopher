
#include "philo.h"


void* philo_needs_to_eat(void *arg)
{
	t_philo *ph;
	struct timeval before;

	ph = (t_philo*)arg;
	gettimeofday(&before, NULL);
	if (ph->thread_id % 2 == 0)
	{
		while (ph->meal_count < ph->must_eat)
		{
			//printf("%lu %d is thinking.\n", timestamp(before), ph->thread_id);
			pthread_mutex_lock(&ph->left);
			printf("%lu %d has taken a left fork.\n", timestamp(before), ph->thread_id);
			pthread_mutex_lock(&ph->right);
			printf("%lu %d has taken a right fork.\n", timestamp(before), ph->thread_id);
			printf("%lu %d is eating.\n", timestamp(before), ph->thread_id);
			usleep(ph->time_to_eat * 1000);
			pthread_mutex_unlock(&ph->right);
			pthread_mutex_unlock(&ph->left);
			usleep(ph->time_to_sleep * 1000);
			printf("%lu %d is sleeping.\n", timestamp(before), ph->thread_id);
			if (ph->must_eat != -1)
				ph->meal_count++;
		}
	}
	else
	{
		while (ph->meal_count < ph->must_eat)
		{
			//printf("%lu %d is thinking.\n", timestamp(before), ph->thread_id);
			usleep(ph->time_to_eat * 1000);
			pthread_mutex_lock(&ph->left);
			printf("%lu %d has taken a right fork.\n", timestamp(before), ph->thread_id);
			pthread_mutex_lock(&ph->right);
			printf("%lu %d has taken a left fork.\n", timestamp(before), ph->thread_id);
			printf("%lu %d is eating.\n", timestamp(before), ph->thread_id);
			pthread_mutex_unlock(&ph->right);
			pthread_mutex_unlock(&ph->left);
			usleep(ph->time_to_sleep * 1000);
			printf("%lu %d is sleeping.\n", timestamp(before), ph->thread_id);
			if (ph->must_eat != -1)
				ph->meal_count++;
		}
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

