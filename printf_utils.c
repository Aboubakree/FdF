/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrid <akrid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:19:57 by akrid             #+#    #+#             */
/*   Updated: 2024/01/14 21:19:58 by akrid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(const char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		s = "(null)";
	while (*s)
		count += ft_putchar(*s++);
	return (count);
}

int	ft_putnbr(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	else
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_puthex(unsigned long n, char *base, char converge)
{
	int	count;

	count = 0;
	if (converge == 'p')
		count += ft_putstr("0x");
	if (n > 15)
	{
		count += ft_puthex(n / 16, base, 'x');
		count += ft_puthex(n % 16, base, 'x');
	}
	else
		count += ft_putchar(base[n]);
	return (count);
}
