/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:09:50 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/07 17:41:12 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

t_cmd	empty_command(char *c)
{
	t_cmd	cmd;

	cmd.cmd_str = ft_calloc(2, sizeof(char *));
	if (!cmd.cmd_str)
		custom_error("Error: Could not allocate memory");
	cmd.cmd_str[0] = ft_strdup(c);
	cmd.command = ft_strdup(c);
	cmd.flags = NULL;
	return (cmd);
}

t_cmd	assign_command(char *arg)
{
	t_cmd	cmd;

	if (arg[0] == 0)
		return (empty_command("\0"));
	cmd.cmd_str = ft_split(arg, ' ');
	if (!cmd.cmd_str)
		custom_error("Error: Could not allocate memory");
	if (cmd.cmd_str[0] == NULL)
	{
		free_array(cmd.cmd_str);
		return (empty_command(" "));
	}
	cmd.command = ft_strdup(cmd.cmd_str[0]);
	if (!cmd.command)
		custom_error("Error: Could not allocate memory");
	cmd.flags = duplicate(&cmd.cmd_str[1]);
	return (cmd);
}

char	*get_fullcommand(char *short_cmd, char **path, int file)
{
	char	*full_command;
	char	*aux;

	while (*path)
	{
		full_command = short_cmd;
		aux = ft_strjoin(*path, full_command);
		if (!aux)
			custom_error("Error: Could not allocate memory");
		full_command = aux;
		if (access(full_command, F_OK | X_OK) == 0)
		{
			free(short_cmd);
			return (full_command);
		}
		free(aux);
		path++;
	}
	if (file != -1)
	{
		ft_putstr_fd(short_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free(short_cmd);
	return (0);
}

char	*check_command(t_cmd cmd, char **path, int file)
{
	if (!cmd.command)
		return (0);
	if (access(cmd.command, F_OK | X_OK) == 0)
		return (cmd.command);
	else
		return (get_fullcommand(cmd.command, path, file));
}
