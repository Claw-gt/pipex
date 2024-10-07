/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/07 17:40:49 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

char	**add_slash(char **path)
{
	char	**full_path;
	int		i;
	char	*aux;

	i = 0;
	full_path = duplicate(path);
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		free(full_path[i]);
		full_path[i] = aux;
		i++;
	}
	return (full_path);
}

void	search_path(char *envp[], t_args *arguments)
{
	char	*path_env;
	char	**path_array;
	char	**env_aux;
	char	**full_path;

	env_aux = envp;
	while (env_aux)
	{
		if (ft_strncmp(*env_aux, "PATH=", 5) == 0)
		{
			path_env = ft_substr(*env_aux, 5, ft_strlen(*env_aux) - 5);
			if (!path_env)
				custom_error("Error: Could not allocate memory");
			path_array = ft_split(path_env, ':');
			if (!path_array)
				custom_error("Error: Could not allocate memory");
			full_path = add_slash(path_array);
			free(path_env);
			free_array(path_array);
			break ;
		}
		env_aux++;
	}
	arguments->path = full_path;
}

void	check_files(char *argv[], t_args *arguments)
{
	int		input_fd;
	int		output_fd;
	int		file_error[2];

	input_fd = 0;
	output_fd = 1;
	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
	{
		perror(argv[1]);
		file_error[0] = 1;
	}
	output_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		perror(argv[4]);
		file_error[1] = 1;
	}
	if (file_error[0] == 1 && file_error[1] == 1)
		exit(EXIT_FAILURE);
	arguments->input_file = input_fd;
	arguments->output_file = output_fd;
}

void	parse_input(int argc, char *argv[], char *envp[], t_args *arguments)
{
	if (argc != 5)
		custom_error("Error: Wrong number of arguments\n");
	check_files(argv, arguments);
	search_path(envp, arguments);
	arguments->cmd1 = assign_command(argv[2]);
	arguments->cmd2 = assign_command(argv[3]);
	arguments->cmd1.command = check_command(arguments->cmd1, arguments->path, \
											arguments->input_file);
	arguments->cmd2.command = check_command(arguments->cmd2, arguments->path, \
											arguments->output_file);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_args	arguments;

	parse_input(argc, argv, envp, &arguments);
	create_pipe(arguments, envp);
	free_elements(&arguments);
	write(1, "Main program started\n", 21);
	return (0);
}
