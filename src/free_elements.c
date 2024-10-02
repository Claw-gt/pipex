/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:10 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/02 12:35:16 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// void	free_partial(char **arr, int num)
// {
// 	int	i;

// 	i = 0;
// 	while (i < num)
// 	{
// 		free (arr[i]);
// 		i++;
// 	}
// 	free (arr);
// }

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
	free_array(arguments->cmd1.cmd_str);
	free(arguments->cmd1.command);
	free_array(arguments->cmd1.flags);
	free_array(arguments->cmd2.cmd_str);
	free(arguments->cmd2.command);
	free_array(arguments->cmd2.flags);
}