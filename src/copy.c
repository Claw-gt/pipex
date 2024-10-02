/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:20:20 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/02 12:41:42 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
		custom_error("Error: Could not allocate memory");
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

t_cmd	assign_command(char *arg)
{
	t_cmd	cmd;
	int		i;
	// int		j;
	// int		flags;

	//flags = 0;
	i = 0;
	//j = 0;
	cmd.cmd_str = ft_split(arg, ' '); //free luego?
	cmd.command = ft_strdup(cmd.cmd_str[0]);
	if (!cmd.cmd_str || !cmd.command)
		custom_error("Error: Could not allocate memory");
	cmd.flags = duplicate(&cmd.cmd_str[1]);
	// while (cmd.cmd_str[++i])
	// 	flags++;
	// cmd.flags = (char **)ft_calloc(flags + 1, sizeof(char *));
	// if (!cmd.flags)
	// 	custom_error("Error: Could not allocate memory");
	// i = 0;
	// while (cmd.cmd_str[++i])
	// {
	// 	cmd.flags[j] = ft_strdup(cmd.cmd_str[i]);
	// 	if (!cmd.flags[j])
	// 		free_array(cmd.flags);
	// 	j++;
	// }
	ft_printf("arg: %s COMMAND 1: %s FLAGS: ", arg, cmd.command);
	i = 0;
	while (cmd.flags[i])
	{
		write(1, cmd.flags[i], ft_strlen(cmd.flags[i]));
		i++;
	}
	write(1, "\n", 1);
	return (cmd);
}

void	change_permissions(char *file)	
{
	char	*envp[1];
	char	*args[4];
	pid_t	pid;

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
	}
}

void	parse_input(int argc, char *argv[], char *envp[], t_args *arguments)
{
	if (argc != 5)
		custom_error("Error: Wrong number of arguments\n");
	check_files(argv, arguments);
	search_path(envp, arguments);
	arguments->cmd1 = assign_command(argv[2]);
	arguments->cmd2 = assign_command(argv[3]);	
	arguments->cmd1.command = check_command(arguments->cmd1, arguments);
	arguments->cmd2.command = check_command(arguments->cmd2, arguments);
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