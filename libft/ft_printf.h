/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:54:30 by clagarci          #+#    #+#             */
/*   Updated: 2024/03/14 19:22:24 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

int	ft_printf(char const *param, ...);

int	ft_putchar(char c);

int	ft_putstr(char *s);

int	ft_putnbr_int(int n);

int	ft_putnbr_uint(unsigned int n, char *base);

int	ft_putnbr_lint(unsigned long int n);

#endif