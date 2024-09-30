/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:39:54 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/30 18:51:27 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void    print_errno(char *str)
{
    perror(str);
	exit (EXIT_FAILURE);
}

void    custom_error(char *str)
{
    ft_putstr_fd(str, 2);
    exit (EXIT_FAILURE);
}