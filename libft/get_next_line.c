/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:46:06 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/06 11:34:32 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concatenate(char *line, ssize_t bytes_read, char *buffer)
{
	char	*aux;

	if (line == NULL && bytes_read != 0)
	{
		line = (char *)malloc(sizeof(char) * 1);
		if (!line)
		{
			free(buffer);
			return (NULL);
		}
		line[0] = '\0';
	}
	aux = ft_strjoin(line, buffer);
	if (!aux)
	{
		free(line);
		free (buffer);
		return (NULL);
	}
	free (line);
	line = aux;
	return (line);
}

char	*read_line(int fd, char *line)
{
	ssize_t	nbytes;
	char	*buffer;

	nbytes = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n') && nbytes != 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free (line);
			free (buffer);
			return (NULL);
		}
		buffer[nbytes] = '\0';
		line = concatenate(line, nbytes, buffer);
		if (!line)
			return (NULL);
	}
	free (buffer);
	return (line);
}

char	*copy_line(char *guide)
{
	char	*line;
	size_t	i;

	i = 0;
	while (guide[i] != '\n' && guide[i] != '\0')
		i++;
	line = ft_substr(guide, 0, i + 1);
	if (!line)
		return (NULL);
	return (line);
}

char	*next_line(char *guide)
{
	char	*new_line;
	char	*ptr_next_line;
	size_t	length;

	length = 0;
	ptr_next_line = ft_strchr(guide, '\n');
	if (!ptr_next_line)
		return (NULL);
	ptr_next_line++;
	if (*ptr_next_line == '\0')
		return (NULL);
	while (ptr_next_line[length] != '\0')
		length++;
	new_line = ft_substr(ptr_next_line, 0, length);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*guide_line;
	char		*line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	new_line = NULL;
	line = NULL;
	guide_line = read_line(fd, guide_line);
	if (!guide_line)
		return (NULL);
	new_line = next_line(guide_line);
	line = copy_line(guide_line);
	free (guide_line);
	if (!line)
		free(new_line);
	else
		guide_line = new_line;
	return (line);
}
