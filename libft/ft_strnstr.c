/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:19:43 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/02 17:41:02 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while ((i < len) && (haystack[i] != '\0'))
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while ((haystack[i + j] == needle[j]) && (haystack[i + j] != '\0'
					|| needle[j] != '\0') && ((i + j) < len))
				j++;
			if (needle[j] == '\0')
				return ((char *) &haystack[i]);
		}
		i++;
	}
	return (0);
}
