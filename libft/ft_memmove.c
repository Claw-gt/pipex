/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:10:59 by clagarci          #+#    #+#             */
/*   Updated: 2024/01/27 16:28:00 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy_backward(char *dest, const char *src, size_t len)
{
	while (len > 0)
	{
		dest[len - 1] = src[len - 1];
		len--;
	}
	return (dest);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dest;
	const char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dest = (char *)dst;
	source = (const char *)src;
	if (dest > source)
		dest = copy_backward(dest, source, len);
	else
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dest);
}
