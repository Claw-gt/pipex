/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/01 13:14:10 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_partial(char **arr, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free (arr[i]);
		i++;
	}
	free (arr);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**duplicate(char **array)
{
	char	**duplicate;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while(array[i++])
		len++;
	duplicate = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!duplicate)
		exit(1);
	i = 0;
	while (array[i])
	{
		duplicate[i] = ft_strdup(array[i]);
		if (!duplicate)
			free_array(duplicate);
		i++;
	}
	return (duplicate);
}

void	search_path(char *envp[], t_args *arguments)
{
	char	*path_env;
	char	**path_array;
	char	**env_aux;

	env_aux = envp;
	while(env_aux)
	{
		if (ft_strncmp(*env_aux, "PATH=", 5) == 0)
		{
			path_env = ft_substr(*env_aux, 5, ft_strlen(*env_aux) - 5);
			if (path_env == NULL)
				custom_error("Error: Could not allocate memory");
			path_array = ft_split(path_env, ':');
			free(path_env);
			if (path_array == NULL)
				custom_error("Error: Could not allocate memory");
			break;
		}
		env_aux++;		
	}
	// int i = 0;
	// while (path_array[i])
	// {
	// 	write(1, path_array[i], ft_strlen(path_array[i]));
	// 	write(1, "\n", 1);
	// 	i++;
	// }
	arguments->path = path_array;
}

t_cmd	search_command(char *cmd)
{
	t_cmd	cmd1;
	//char	*aux;
	int		i;
	int		j;
	int		flags;

	flags = 0;
	i = 0;
	j = 0;
	cmd1.cmd_str = ft_split(cmd, ' '); //free luego?
	cmd1.command = ft_strdup(cmd1.cmd_str[0]);
	if (!cmd1.cmd_str || !cmd1.command)
		exit(1);
	while (cmd1.cmd_str[++i])
		flags++;
	cmd1.flags = (char **)ft_calloc(flags + 1, sizeof(char *));
	if (!cmd1.flags)
		exit(1);
	i = 0;
	while (cmd1.cmd_str[++i])
	{
		cmd1.flags[j] = ft_strdup(cmd1.cmd_str[i]);
		if (!cmd1.flags[j])
			free_partial(cmd1.flags, j);
		j++;
	}
	ft_printf("arg: %s COMMAND 1: %s FLAGS: ", cmd, cmd1.command);
	i = 0;
	while (cmd1.flags[i])
	{
		write(1, cmd1.flags[i], ft_strlen(cmd1.flags[i]));
		i++;
	}
	write(1, "\n", 1);
	return (cmd1);
}

void	change_permissions(char *file)	
{
	char	*envp[1];
	char	*args[4];
	int		pid;

	pid = fork();
	if (pid == -1)
		print_errno("Fork failed");
	if (pid == 0)
	{
		args[0] = "/usr/bin/chmod";
		args[1] = "644";
		args[2] = file;
		args[3] = NULL;
		*envp = NULL;	
		execve(args[0], args, envp);
		perror("Could not execve");
	}
	else
		wait(NULL);
}

/*if open() fails, -1 is returned and errno is set to indicate the error.
The same happens with access().
When it creates outfile, it has no permissions at all*/
void	check_files(char *argv[], t_args *arguments)
{
	int	input_fd;
	int	output_fd;

	input_fd = 0;
	output_fd = 1;
	if (access(argv[1], F_OK) == 0)
	{
		input_fd = open(argv[1], O_RDONLY);
		if (input_fd == -1)
			print_errno(argv[1]);
	}
	else
		print_errno(argv[1]);
	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], R_OK|W_OK) != 0)
			change_permissions(argv[4]);
		output_fd = open(argv[4], O_WRONLY|O_TRUNC);
		if (output_fd == -1)
			print_errno(argv[4]);
	}
	else
	{
		output_fd = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC);
		write(1, "File created\n", 13);
		if (output_fd == -1)
			print_errno(argv[4]);
		change_permissions(argv[4]);
	}
	arguments->input_file = input_fd;
	arguments->output_file = output_fd;
	// printf("input fd: %d output fd: %d", input_fd, output_fd);
	// close (input_fd);
	// close (output_fd);
}

char	*check_command(t_cmd cmd, t_args *arguments)
{
	int		i;
	char	*path_aux;
	char	*full_command;
	char	*aux;

	i = 0;
	if (access(cmd.command, F_OK|X_OK) == 0)
		return (cmd.command);
	else
	{
		while (arguments->path[i])
		{
			full_command = cmd.command;
			path_aux = ft_strjoin(arguments->path[i], "/");
			if (!path_aux)
				custom_error("Error: Could not allocate memory");
			aux = ft_strjoin(path_aux, full_command);
			if (!aux)
				custom_error("Error: Could not allocate memory");
			free (path_aux);
			full_command = aux;
			if (access(full_command, F_OK|X_OK) == 0)
			{
				free(cmd.command);
				return (full_command);
			}
			i++;
			free(aux);
		}
		ft_putstr_fd(cmd.command, 2);
		custom_error(": command not found\n");
		return (NULL);
		// ft_putstr_fd(": command not found\n", 2);
		// exit (1);
	}
}

void	parse_input(int argc, char *argv[], char *envp[], t_args *arguments)
{
	if (argc != 5)
		custom_error("Error: Wrong number of arguments\n");
	check_files(argv, arguments);
	search_path(envp, arguments);
	arguments->cmd1 = search_command(argv[2]);
	arguments->cmd2 = search_command(argv[3]);	
	arguments->cmd1.command = check_command(arguments->cmd1, arguments);
	arguments->cmd2.command = check_command(arguments->cmd2, arguments);
}

int	main(int argc, char *argv[], char *envp[])
{
	
	t_args	arguments;

	parse_input(argc, argv, envp, &arguments);
	create_pipe(arguments, envp);
	free_array(arguments.path);
	free_array(arguments.cmd1.cmd_str);
	free(arguments.cmd1.command);
	free_array(arguments.cmd1.flags);
	free_array(arguments.cmd2.cmd_str);
	free(arguments.cmd2.command);
	free_array(arguments.cmd2.flags);
	write(1, "Main program started\n", 21);
	return (0);
}