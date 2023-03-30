/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:32 by lsun              #+#    #+#             */
/*   Updated: 2023/03/30 20:23:52 by linlinsun        ###   ########.fr       */
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

long timestamp(struct  timeval before)
{
	long timestamp;
	struct timeval after;

	gettimeofday(&after, NULL);
	timestamp = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_usec - before.tv_usec)/1000;
	return(timestamp);
}

void ft_usleep(int mseconds)
{
	struct timeval time;
	//unsigned long long	end;

	gettimeofday(&time, NULL);
	//end = mseconds * 1000;
	while (timestamp(time) < mseconds)
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
