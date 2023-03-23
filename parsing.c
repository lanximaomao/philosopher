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
