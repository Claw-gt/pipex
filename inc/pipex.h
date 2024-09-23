/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:23:15 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/23 19:15:50 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

enum
{
	ERROR_BLOCK_OPERATION = 1,
	ERROR_FILE = 2,
	ERROR_UNKNOWN_PROCESS = 3,
	ERROR_INTERRUPT_CALL = 4,
	ERROR_IO = 5,
	ERROR_ADDRESS = 6,
	ERROR_LONG_ARGS = 7,
	ERROR_EXEC_FORMAT = 8,
	ERROR_FD = 9,
	ERROR_CHILD_PROC = 10,
    ERROR_RESOURCE_UNAVAILABLE = 11,
    ERROR_MEMORY_ALLOC = 12,
    ERROR_NO_PERMISSION = 13,
};
#endif