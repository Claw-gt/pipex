/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:34:14 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/03 14:57:32 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	length;
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	concat = (char *)malloc(length + 1);
	if (concat == NULL)
		return (NULL);
	ft_strlcpy(concat, s1, ft_strlen(s1) + 1);
	ft_strlcat(concat, s2, length + 1);
	return (concat);
}
