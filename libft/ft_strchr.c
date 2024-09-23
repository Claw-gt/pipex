/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:10:19 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/02 16:10:50 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&ptr[i]);
	return (NULL);
}
