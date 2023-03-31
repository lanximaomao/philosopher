/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:32 by lsun              #+#    #+#             */
/*   Updated: 2023/03/31 13:05:13 by linlinsun        ###   ########.fr       */
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
		if (result > 9223372036854775807)
		{
			if (sign > 0)
				return (-1);
			else
				return (1);
		}
		str++;
	}
	if (*str != '\0' && (*str < 0 || *str > 9))
		return(-1);
	return (result * sign);
}

unsigned long long timestamp(unsigned long long start)
{
	unsigned long long current_time;

	current_time = get_current_time();
	//printf("current_time is %llu\n", current_time);
	//printf("timestamp %llu\n", current_time - start);
	return(current_time - start);
}

/* get current time in ms */
unsigned long long get_current_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(int mseconds)
{
	unsigned long long	current_time;

	current_time = get_current_time();
	//end = mseconds * 1000;
	while (timestamp(current_time) < mseconds)
	{
		usleep(1);
		//end -= 500;
	}
	//usleep(end);
}

// one second = 1,000,000 microseconds

//int main()
//{
//	struct timeval before;
//	struct timeval after;
//	gettimeofday(&before, NULL);
//	//printf("seconds: %ld\nmicrosecond: %d\n", before.tv_sec, before.tv_usec);
//	usleep(100000); // 100 miliseconds
//	gettimeofday(&after, NULL);
//	//printf("seconds: %ld\nmicrosecond: %d\n", after.tv_sec, after.tv_usec);
//	printf("time difference: %ld\n", (after.tv_usec-before.tv_usec) / 1000 + (after.tv_sec - before.tv_sec) * 1000);
//}
