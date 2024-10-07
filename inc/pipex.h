/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:23:15 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/07 16:22:45 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include "../libft/libft.h"
# define DEBUG 1
# define READ_END 0
# define WRITE_END 1

typedef struct s_cmd
{
	char	**cmd_str;
	char	*command;
	char	**flags;
}				t_cmd;

typedef struct s_args
{
	int		input_file;
	int		output_file;
	char	**path;
	t_cmd	cmd1;
	t_cmd	cmd2;
}				t_args;

void	print_errno(char *str);

void	custom_error(char *str);

char	*check_command(t_cmd cmd, char **path, int file);

t_cmd	assign_command(char *arg);

void	execute_cmd(char **envp, t_cmd cmd);

void	create_pipe(t_args arguments, char **envp);

char	**duplicate(char **array);

void	free_elements(t_args *arguments);

void	free_array(char **array);

#endif