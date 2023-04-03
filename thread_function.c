
#include "philo.h"


void* philo_needs_to_eat(void *arg)
{
	int i;
	t_philo *ph;


	i = 0;
	ph = (t_philo*)arg;

	if (ph->thread_id % 2 != 0)
		usleep(50);
	while (ph->meal_count == -1 || ph->meal_count < ph->must_eat)
	{
		//printf("start = %llu && ph->last_meal = %llu\n", ph->start, ph->last_meal);
		if (ph->is_alive != 1)
			break;
		//if (timestamp(ph->last_meal) >= ph->time_to_die)
		//{
		//	ph->is_alive = 0;
		//	break;
		//}
		printf("%llu %d is thinking\n", timestamp(ph->start), ph->thread_id);
		pthread_mutex_lock(ph->mutex_left);
		//*(ph->fork_left) = ph->thread_id;
		printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
		pthread_mutex_lock(ph->mutex_right);
		//*(ph->fork_right) = ph->thread_id;
		printf("%llu %d has taken a fork\n", timestamp(ph->start), ph->thread_id);
		if (ph->is_alive == 1)
		{
			printf("%llu %d is eating\n", timestamp(ph->start), ph->thread_id);
			//ft_usleep(ph->time_to_eat);
			ph->previous_meal = ph->last_meal;
			ph->last_meal = get_current_time();
			usleep(ph->time_to_eat * 1000);
		}
		else
			return(NULL);
		//*(ph->fork_right) = 0;
		//*(ph->fork_left) = 0;
		pthread_mutex_unlock(ph->mutex_right);
		pthread_mutex_unlock(ph->mutex_left);

		//ft_usleep(ph->time_to_sleep);
		if (ph->is_alive != 1)
			break;
		printf("%llu %d is sleeping\n", timestamp(ph->start), ph->thread_id);
		usleep(ph->time_to_sleep * 1000);
		if (ph->must_eat != -1)
			ph->meal_count++;
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
	t_philo *ph;

	i = 0;
	j = 0;
	ph = (t_philo*)arg;

	usleep(ph[0].time_to_die);
	while (1)
	{
		if (ph[i].last_meal - ph[i].previous_meal >= ph[i].time_to_die)
		{
			ph->is_alive = 0;
			//printf("\n\n\n%llu, %llu, %d\n", ph[i].last_meal, ph[i].start, ph[i].time_to_die);
			break;
		}
		i++;
		if (i >= ph[0].num)
			i = 0;
		//printf("i = %d\n", i);
	}
	while (j < ph[0].num)
	{
		//if ( j != i)
			ph[j].is_alive = 0;
		j++;
	}
	//printf("i = %d\n", i);
	death_announcement(timestamp(ph[i].start), ph[i].thread_id);
	//printf("hello from monitor.\n");
	//printf("philo %d\n status %d\n", ph[1].thread_id, ph[1].status);
	//death_announcement(timestamp(start), ph->thread_id);
	return(NULL);
}

