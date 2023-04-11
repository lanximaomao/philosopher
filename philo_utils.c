/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:32 by lsun              #+#    #+#             */
/*   Updated: 2023/04/11 10:35:52 by lsun             ###   ########.fr       */
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

void	ft_usleep(unsigned long long microseconds)
{
	unsigned long long	current_time;

	current_time = get_current_time();
	while (timestamp(current_time) * 1000 < microseconds)
	{
		usleep(500);
	}
}
