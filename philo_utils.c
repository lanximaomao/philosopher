/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:32 by lsun              #+#    #+#             */
/*   Updated: 2023/06/02 13:51:30 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_isnum(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' && (*str < 0 || *str > 9))
		return (-1);
	return (result * sign);
}

unsigned long long	timestamp(unsigned long long start)
{
	unsigned long long	current_time;

	current_time = get_current_time();
	return (current_time - start);
}

unsigned long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
** flag 0 means no need to do mutex
** -1 means no need to sleep, 0 means sleep the whole time
*/
int	ft_usleep(unsigned long long microseconds, t_philo *ph, int flag)
{
	int status;
	unsigned long long	current_time;

	status = 0;
	current_time = get_current_time();
	while (timestamp(current_time) * 1000 < microseconds)
	{
		if (flag == 1)
		{
			status = check_status(ph);
			if (status == 1)// -1, 0, 1
				usleep(500);
			else
				return (-1);
		}
		else
			usleep(500);
	}
	return(0);
}
