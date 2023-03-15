/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:05:24 by linlinsun         #+#    #+#             */
/*   Updated: 2023/03/15 23:46:34 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

}					t_philo;

typedef struct s_carry
{
	int				*forks;
	t_philo			each_philo;
	pthread_mutex_t	mutex_forks;

}					t_carry;

/* libft */
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_digit_num(long n);

/* printf */
int					ft_putchar_printf(char c, int fd);
int					ft_putstr_printf(char *s, int fd);
int					ft_putnbr_printf(int n, int fd);
int					ft_putnbr_unsigned_printf(unsigned int n, int fd);
int					ft_printf_ptr(unsigned long long n);
int					ft_hexa_deci_big(unsigned int n);
int					ft_hexa_deci_small(unsigned int n);

#endif
