/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:47:33 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/03 15:49:09 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*ptr;
	const char	*aux;
	size_t		len;

	len = 0;
	if (!s1)
		return (NULL);
	aux = s1;
	while (s1[len] != '\0')
		len++;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	while (len-- > 0)
		ptr[len] = aux[len];
	return (ptr);
}
