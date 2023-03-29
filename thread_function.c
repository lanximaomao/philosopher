
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
			pthread_mutex_lock(&ph->left);
			printf("%lu philo %d took a left fork.\n", timestamp(before), ph->thread_id);
			pthread_mutex_lock(&ph->right);
			printf("%lu philo %d took a right fork.\n", timestamp(before), ph->thread_id);
			printf("%lu philo %d is eating.\n", timestamp(before), ph->thread_id);
			usleep(ph->time_to_eat);
			pthread_mutex_unlock(&ph->right);
			pthread_mutex_unlock(&ph->left);
			if (ph->must_eat != -1)
				ph->meal_count++;
		}
	}
	else
	{
		while (ph->meal_count < ph->must_eat)
		{
			usleep(ph->time_to_eat/2);
			pthread_mutex_lock(&ph->right);
			printf("%lu philo %d took a left fork.\n", timestamp(before), ph->thread_id);
			pthread_mutex_lock(&ph->left);
			printf("%lu philo %d is eating.\n", timestamp(before), ph->thread_id);
			pthread_mutex_unlock(&ph->left);
			pthread_mutex_unlock(&ph->right);
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

