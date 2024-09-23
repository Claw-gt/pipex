/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:14:51 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/02 18:16:16 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length_src;
	size_t	length_dest;

	i = 0;
	length_src = 0;
	length_dest = 0;
	if (dst == NULL && dstsize == 0)
		return (0);
	while (src[length_src] != '\0')
		length_src++;
	while (dst[length_dest] != '\0')
		length_dest++;
	if (dstsize > length_dest)
	{
		while (src[i] != '\0' && i < (dstsize - length_dest - 1))
		{
			dst[length_dest + i] = src[i];
			i++;
		}
		dst[length_dest + i] = '\0';
		return (length_dest + length_src);
	}
	else
		return (dstsize + length_src);
}
