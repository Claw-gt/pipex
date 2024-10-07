/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:19:10 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/07 16:21:18 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**duplicate(char **array)
{
	char	**duplicate;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (array[i++])
		len++;
	duplicate = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!duplicate)
		custom_error("Error: Could not allocate memory");
	i = 0;
	while (array[i])
	{
		duplicate[i] = ft_strdup(array[i]);
		if (!duplicate)
			free_array(duplicate);
		i++;
	}
	return (duplicate);
}
