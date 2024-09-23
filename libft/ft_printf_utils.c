/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:15:08 by clagarci          #+#    #+#             */
/*   Updated: 2024/03/16 16:30:25 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putnbr_int(int n)
{
	int	num_printed;

	num_printed = 0;
	if (n == INT_MIN)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		num_printed++;
		n *= -1;
	}
	if (n > 9)
	{
		num_printed += ft_putnbr_int(n / 10);
		if (num_printed == -1)
			return (-1);
	}
	if (ft_putchar(n % 10 + '0') == -1)
		return (-1);
	num_printed++;
	return (num_printed);
}

int	ft_putnbr_uint(unsigned int n, char *base)
{
	int		num_printed;
	size_t	len_base;

	num_printed = 0;
	len_base = 0;
	while (base[len_base] != '\0')
		len_base++;
	if (n >= len_base)
	{
		num_printed += ft_putnbr_uint(n / len_base, base);
		if (num_printed == -1)
			return (-1);
	}
	if (ft_putchar(base[n % len_base]) == -1)
		return (-1);
	num_printed++;
	return (num_printed);
}

int	ft_putnbr_lint(unsigned long int n)
{
	int		num_printed;
	char	*hex;

	hex = "0123456789abcdef";
	num_printed = 0;
	if (n > 15)
	{
		num_printed += ft_putnbr_lint(n / 16);
		if (num_printed == -1)
			return (-1);
	}
	if (ft_putchar(hex[n % 16]) == -1)
		return (-1);
	num_printed++;
	return (num_printed);
}
