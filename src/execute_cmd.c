/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:48:46 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/04 13:20:16 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	command_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	execute_cmd(char **envp, t_cmd cmd)
{
	char	**argv;
	int		i;

	i = 1;
	if (cmd.command == NULL)
		exit (EXIT_FAILURE);
	argv = ft_calloc(command_len(cmd.cmd_str) + 1, sizeof(char *));
	if (!argv)
		custom_error("Error: Could not allocate memory");
	argv[0] = cmd.command;
	while (cmd.cmd_str[i])
	{
		argv[i] = cmd.cmd_str[i];
		i++;
	}
	argv[i] = NULL;
	execve(argv[0], argv, envp);
	free_array(argv);
	//if (DEBUG == 1)
		print_errno("");
	//exit (EXIT_FAILURE);
}
