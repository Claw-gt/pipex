/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:10 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/07 17:40:47 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_elements(t_args *arguments)
{
	free_array(arguments->path);
	if (arguments->cmd1.cmd_str != NULL)
	{
		free_array(arguments->cmd1.cmd_str);
		free(arguments->cmd1.command);
		if (arguments->cmd1.flags)
			free_array(arguments->cmd1.flags);
	}
	if (arguments->cmd2.cmd_str != NULL)
	{
		free_array(arguments->cmd2.cmd_str);
		free(arguments->cmd2.command);
		if (arguments->cmd2.flags)
			free_array(arguments->cmd2.flags);
	}
}
