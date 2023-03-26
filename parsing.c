#include "philo.h"

int parsing(t_philo *ph, int argc, char** argv)
{
	int i;

	if (argc < 4 || argc > 5)
	{
		printf("wrong number of arguments.\n");
		return (0);
	}
	ph->num = ft_atoi(argv[0]);
	ph->time_to_die = ft_atoi(argv[1]);
	ph->time_to_eat = ft_atoi(argv[2]);
	ph->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		ph->must_eat = ft_atoi(argv[4]);
	else
		ph->must_eat = 1000;
	if (ph->num > 0 && ph->time_to_die > 0 && ph->time_to_eat > 0 && ph->time_to_sleep >= 0 && ph->must_eat > 0)
		return (1);
	printf("wrong input.\n");
	return(0);
}

void philo_init(t_philo *ph, t_philo *phs)
{
	int i;

	i = 0;
	while (i < ph->num + 1)
	{
		(phs[i]).num = ph->num;
		(phs[i]).time_to_die = ph->time_to_die;
		(phs[i]).time_to_eat = ph->time_to_eat;
		(phs[i]).time_to_sleep = ph->time_to_sleep;
		(phs[i]).must_eat = ph->must_eat;
		(phs[i]).thread_id = i;
		(phs[i]).is_alive = 1;
		(phs[i]).left = 0;
		(phs[i]).right = 0;
		i++;
	}
}
