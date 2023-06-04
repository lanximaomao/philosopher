/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:27:08 by linlinsun         #+#    #+#             */
/*   Updated: 2023/06/04 10:37:13 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

static int	ft_putchar_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	ft_putstr_printf(char *s, int fd)
{
	int	i;
	int	count;

	count = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}

static int	ft_putnbr_printf(int n, int fd)
{
	int	count;

	count = 1;
	if (n < 0 && n != -2147483648)
	{
		ft_putchar_printf('-', fd);
		n = n * (-1);
		count++;
	}
	if (n == -2147483648)
	{
		ft_putchar_printf('-', fd);
		ft_putchar_printf('0' + 2, fd);
		count += 2;
		n = 147483648;
	}
	if (n >= 10)
	{
		count += ft_putnbr_printf(n / 10, fd);
	}
	ft_putchar_printf(n % 10 + 48, fd);
	return (count);
}

int	ft_check_format(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_printf(va_arg(ap, int), 1);
	else if (c == 's')
		count += ft_putstr_printf(va_arg(ap, char *), 1);
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_printf(va_arg(ap, int), 1);
	else if (c == '%')
		count += ft_putchar_printf('%', 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	ap;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			count += ft_check_format(ap, str[i + 1]);
			i++;
		}
		else
			count += ft_putchar_printf(str[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
