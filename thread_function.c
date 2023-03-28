
#include "philo.h"


void* philo_needs_to_eat(void *arg)
{
	t_philo *ph;
	struct timeval before;

	ph = (t_philo*)arg;
	gettimeofday(&before, NULL);
	if (ph->thread_id % 2 == 0)
	{
		printf("%lu philo %d and I can eat first.\n", timestamp(before), ph->thread_id);
		sleep(4);
	}
	else
	{
		printf("%lu philo %d and I will wait first.\n", timestamp(before), ph->thread_id);
		sleep(5);
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

