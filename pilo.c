/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pilo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:55:47 by lsun              #+#    #+#             */
/*   Updated: 2023/03/15 14:11:46 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* func()
{
	printf("msg from threads pilo.\n");
	return (NULL);
}

int main()
{
	int i;

	i = 0;
	pthread_t pilo[4];
	while (i < 4)
	{
		if(pthread_create(&pilo[i], NULL, &func, NULL) != 0)
		{
			printf("error in creating threads.\n");
			return(0);
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(pilo[i], NULL) != 0)
		{
			printf("error in joining threads.\n");
			return(0);
		}
		i++;
	}
	return(0);
}
