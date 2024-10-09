/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:39:54 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/09 17:27:25 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	print_errno(char *str)
{
	perror(str);
	exit (EXIT_FAILURE);
}

void	command_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	custom_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}
