/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:53:35 by clagarci          #+#    #+#             */
/*   Updated: 2024/02/03 12:27:37 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_array(char **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free (arr[i]);
		i++;
	}
	free (arr);
	return (NULL);
}

static char	*move_pointer(char *arr, char c)
{
	while (*arr == c && *arr != '\0')
		arr++;
	return (arr);
}

static int	to_count(const char *arr, char c, int option)
{
	int	words;
	int	i;
	int	letters;

	letters = 0;
	i = 0;
	words = 0;
	while (arr[i] != '\0')
	{
		while (arr[i] == c && arr[i] != '\0')
			i++;
		if (arr[i] != c && arr[i] != '\0')
		{
			words++;
			while (arr[i] != c && arr[i] != '\0')
			{
				letters++;
				i++;
			}
			if (option == 1)
				return (letters);
		}
	}
	return (words);
}

char	*to_copy(char *temp, char *array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		array[i] = temp[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	*temp;
	char	**array;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	temp = (char *)s;
	array = (char **)ft_calloc(to_count(s, c, 0) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (i < to_count(s, c, 0))
	{
		temp = move_pointer(temp, c);
		array[i] = (char *)ft_calloc(to_count(temp, c, 1) + 1, sizeof(char));
		if (array[i] == NULL)
			return (free_array(array, i));
		array[i] = to_copy(temp, array[i], to_count(temp, c, 1));
		temp += to_count(temp, c, 1);
		i++;
	}
	return (array);
}
