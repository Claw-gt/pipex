/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:23:15 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/29 20:00:33 by clagarci         ###   ########.fr       */
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

void    print_error(char *str);

void    execute_cmd(t_args args, char **envp);
#endif