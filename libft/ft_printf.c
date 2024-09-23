/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 22:29:09 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/18 15:06:23 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress(unsigned long p)
{
	int	num_printed;
	int	aux;

	aux = 0;
	num_printed = 0;
	aux = ft_putstr("0x");
	if (aux == -1)
		return (-1);
	num_printed += aux;
	aux = ft_putnbr_lint(p);
	if (aux == -1)
		return (-1);
	num_printed += aux;
	return (num_printed);
}

int	convert_param(va_list args, char character)
{
	if (character == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (character == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (character == 'p')
		return (ft_putaddress(va_arg(args, unsigned long)));
	else if (character == 'd' || character == 'i')
		return (ft_putnbr_int(va_arg(args, int)));
	else if (character == 'u')
		return (ft_putnbr_uint(va_arg(args, unsigned int), "0123456789"));
	else if (character == 'x')
		return (ft_putnbr_uint(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (character == 'X')
		return (ft_putnbr_uint(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (character == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(char const *param, ...)
{
	va_list	args;
	int		char_printed;
	int		aux;

	aux = 0;
	char_printed = 0;
	va_start(args, param);
	while (*param != '\0')
	{
		if (*param == '%' && *(++param))
		{
			aux = convert_param(args, *param);
			if (aux == -1)
				return (-1);
			char_printed += aux;
		}
		else if (ft_putchar(*param) == -1)
			return (-1);
		else
			char_printed++;
		param++;
	}
	va_end (args);
	return (char_printed);
}
