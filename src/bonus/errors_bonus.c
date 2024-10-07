/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:39:54 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/07 17:40:44 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	print_errno(char *str)
{
	perror(str);
	exit (EXIT_FAILURE);
}

void	custom_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit (EXIT_FAILURE);
}
