/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:46:54 by lsun              #+#    #+#             */
/*   Updated: 2023/06/02 13:06:01 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int argc, char **argv, t_arg *arg)
{
	arg->num = ft_atoi_isnum(argv[0]);
	arg->time_to_die = ft_atoi_isnum(argv[1]);
	arg->time_to_eat = ft_atoi_isnum(argv[2]);
	arg->time_to_sleep = ft_atoi_isnum(argv[3]);
	if (argc == 5)
	{
		arg->must_eat = ft_atoi_isnum(argv[4]);
		if (arg->must_eat == 0)
			printf("Must eat is zero. Are you kidding me?!\n");
		else if (arg->must_eat < 0)
			printf("Must eat should be a unsigned int.\n");
		if (arg->must_eat <= 0)
			return (0);
	}
	else
		arg->must_eat = 2147483647;
	if (parsing_error(arg) == 0)
		return (0);
	if (argc == 4)
		arg->must_eat = 2147483647;
	return (1);
}

int	parsing_error(t_arg *arg)
{
	if (arg->num <= 0 || arg->time_to_die <= 0 || arg->time_to_eat < 0
		|| arg->time_to_sleep < 0)
	{
		if (arg->num == 0)
			printf("Are you sure to start the game without any philos?\n");
		if (arg->time_to_die == 0)
			printf("Time to die is zero.\n");
		else
			printf("wrong input.\n");
		return (0);
	}
	return (1);
}
