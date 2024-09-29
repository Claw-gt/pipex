/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:48:46 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/29 20:02:52 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void    execute_cmd(t_args args, char **envp)
{
    char	**argv;
	(void)	envp;

	argv = ft_calloc(3, sizeof(char *));
	argv[0] = args.cmd1.command;
	argv[1] = args.cmd1.flags[0];
	argv[2] = NULL;
    execve(argv[0], argv, envp);
	perror("Could not execve");
    write(1, "hello", 5);
}