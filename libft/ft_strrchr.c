/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:04:00 by clagarci          #+#    #+#             */
/*   Updated: 2024/01/21 15:19:18 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (s[i] != '\0')
		i++;
	if (s[i] == (char) c)
		return (&ptr[i]);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (&ptr[i]);
		i--;
	}
	return (0);
}
