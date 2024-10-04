/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/04 15:09:16 by clagarci         ###   ########.fr       */
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
	while (array[i++])
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
	int		i;

	i = 0;
	if (arg[0] == 0)
		return(empty_command("\0"));
	cmd.cmd_str = ft_split(arg, ' ');
	if (!cmd.cmd_str)
		custom_error("Error: Could not allocate memory");
	if (cmd.cmd_str[0] == NULL)
	{
		free_array(cmd.cmd_str);
		return(empty_command(" "));
	}
	cmd.command = ft_strdup(cmd.cmd_str[0]);
	if (!cmd.command)
		custom_error("Error: Could not allocate memory");
	cmd.flags = duplicate(&cmd.cmd_str[1]);
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

// void	change_permissions(char *file)
// {
// 	char	*envp[1];
// 	char	*args[4];
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		print_errno("Fork failed");
// 	if (pid == 0)
// 	{
// 		args[0] = "/usr/bin/chmod";
// 		args[1] = "644";
// 		args[2] = file;
// 		args[3] = NULL;
// 		*envp = NULL;
// 		execve(args[0], args, envp);
// 		print_errno("Execve failed");
// 	}
// 	else
// 		wait(NULL);
// }

/*if open() fails, -1 is returned and errno is set to indicate the error.
The same happens with access().*/
/*Must display error of infile (no exist) and of utfile (permission denied)*/
void	check_files(char *argv[], t_args *arguments)
{
	int		input_fd;
	int		output_fd;
	pid_t	files_pid[2];
	int		status[2];

	input_fd = 0;
	output_fd = 1;
	input_fd = open(argv[1], O_RDONLY);
	files_pid[0] = fork();
	if (files_pid[0] == 0)
	{
		if (input_fd == -1)
			print_errno(argv[1]);
		exit(EXIT_SUCCESS);
	}
	output_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	files_pid[1] = fork();
	if (files_pid[1] == 0)
	{
		if (output_fd == -1)
			print_errno(argv[4]);
		exit(EXIT_SUCCESS);
	}
	wait(&status[0]);
	wait(&status[1]);
	// Si ambos archivos fallan -> parar el programa
	if (WEXITSTATUS(status[0]) != EXIT_SUCCESS && \
		WEXITSTATUS(status[1]) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
	arguments->input_file = input_fd;
	arguments->output_file = output_fd;
}

char	*get_fullcommand(char *short_cmd, char **path, int file)
{
	int		i;
	char	*full_command;
	char	*aux;

	i = -1;
	while (path[++i])
	{
		full_command = short_cmd;
		aux = ft_strjoin(path[i], full_command);
		if (!aux)
			custom_error("Error: Could not allocate memory");
		full_command = aux;
		if (access(full_command, F_OK | X_OK) == 0)
		{
			free(short_cmd);
			return (full_command);
		}
		free(aux);
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

void	parse_input(int argc, char *argv[], char *envp[], t_args *arguments)
{
	if (argc != 5)
		custom_error("Error: Wrong number of arguments\n");
	check_files(argv, arguments);
	search_path(envp, arguments);
	arguments->cmd1 = assign_command(argv[2]);
	arguments->cmd2 = assign_command(argv[3]);
	arguments->cmd1.command = check_command(arguments->cmd1, arguments->path, arguments->input_file);
	arguments->cmd2.command = check_command(arguments->cmd2, arguments->path, arguments->output_file);
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
