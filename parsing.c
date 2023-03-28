/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:02:10 by lsun              #+#    #+#             */
/*   Updated: 2023/03/28 19:02:21 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int parsing(int argc, char** argv, t_arg *arg)
{
	arg->num = ft_atoi_isnum(argv[0]);
	arg->time_to_die = ft_atoi_isnum(argv[1]);
	arg->time_to_eat = ft_atoi_isnum(argv[2]);
	arg->time_to_sleep = ft_atoi_isnum(argv[3]);
	if (argc == 5)
		arg->must_eat = ft_atoi_isnum(argv[4]);
	if (arg->num <= 0 || arg->time_to_die <= 0 || arg->time_to_eat < 0 || arg->time_to_sleep < 0 || arg->must_eat <= 0)
	{
		if (arg->num == 0)
			printf("Are you sure to start the game without any philos?\n");
		if (arg->time_to_die == 0)
			printf("Time to die is zero. Very sad, I died immediately.\n");
		if (arg->must_eat == 0)
			printf("Must eat is zero. I am good, no more eating. Thanks!\n");
		else
			printf("wrong input.\n");
		return (0);
	}
	if (argc == 4)
		arg->must_eat = -1;
	return(1);
}
