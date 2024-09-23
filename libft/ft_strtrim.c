/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:49:26 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/04 12:55:16 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		forw;
	size_t		back;
	char		*trimstr;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	forw = 0;
	back = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[forw]) && forw < (ft_strlen(s1) / 2))
		forw++;
	while (ft_strchr(set, s1[back]) && back >= forw)
		back--;
	trimstr = (char *)malloc(sizeof(char) * (back - forw + 2));
	if (trimstr == NULL)
		return (NULL);
	ft_strlcpy(trimstr, s1 + forw, back - forw + 2);
	return (trimstr);
}
