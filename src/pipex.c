/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/27 18:35:44 by clagarci         ###   ########.fr       */
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
			{
				perror("Error: Could not allocate memory");
				exit (1);
			}
			path_array = ft_split(path_env, ':');
			free(path_env);
			if (path_array == NULL)
			{
				perror("Error: Could not allocate memory");
				exit (1);
			}
			break;
		}
		env_aux++;		
	}
	ft_printf("\npath: %s\n", path_array[2]);
	arguments->path = path_array;
	free_array(path_array);
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
	if (!cmd1.cmd_str)
		exit(1);
	cmd1.command = ft_strdup(cmd1.cmd_str[0]);
	if (!cmd1.command)
		exit(1);
	while (cmd1.cmd_str[++i])
		flags++;
	printf("FLAGS: %d", flags);
	cmd1.flags = (char **)ft_calloc(flags + 1, sizeof(char *));
	if (!cmd1.flags)
		exit(1);
	// cmd1.flags = ft_strdup("");
	i = 0;
	while (cmd1.cmd_str[++i])
	{
		cmd1.flags[j] = ft_strdup(cmd1.cmd_str[i]);
		if (!cmd1.flags)
			free_array(cmd1.flags);
		j++;
	}
	// printf("Command flag: %s", cmd1.command);
	// while (cmd1.cmd_str[++i])
	// {
	// 	cmd1.flags[i - 1] =  cmd1.cmd_str[i];
	// }
	// cmd2.cmd_str = ft_split(argv[3], ' ');
	// cmd2.command = ft_strdup(cmd2.cmd_str[0]);

	ft_printf("arg: %s COMMAND 1: %s FLAG1: %s\n", cmd, cmd1.command, cmd1.flags[0]);
	//ft_printf("arg: %s COMMAND 2: %s", argv[3], cmd2.command);	
	// free_array(cmd1.cmd_str);
	// free_array(cmd2.cmd_str);
	// free(cmd1.command);
	// free(cmd2.command);
	return (cmd1);
}

void	change_permissions(char *file)	
{
	char	*envp[1];
	char	*args[4];
	
	args[0] = "/usr/bin/chmod";
	args[1] = "644";
	args[2] = file;
	args[3] = NULL;
	*envp = NULL;	
	execve(args[0], args, envp);
    perror("Could not execve");
}

/*if open() fails, -1 is returned and errno is set to indicate the error.
The same happens with acces().
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
		{
			// ft_putstr_fd(strerror(errno), 2);
			// write(2, "\n", 1);
			perror(argv[1]);
			exit (1);
		}
	}
	else
	{
		// ft_putstr_fd(strerror(errno), 2);
		// write(2, "\n", 1);
		perror(argv[1]);
		exit (1);
	}
	// output_fd = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC);
	// if (output_fd == -1)
	// {
	// 	perror(argv[4]);
	// 	exit (1);
	// }
	// change_permissions(argv[4]);
	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], R_OK|W_OK) != 0)
			change_permissions(argv[4]);
		output_fd = open(argv[4], O_WRONLY|O_TRUNC);
	}
	else
	{
		output_fd = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC);
		if (output_fd == -1)
		{
			// ft_putstr_fd(strerror(errno), 2);
			// write(2, "\n", 1);
			perror(argv[4]);
			exit (1);
		}
		change_permissions(argv[4]);
	}
	arguments->input_file = input_fd;
	arguments->output_file = output_fd;
	printf("input fd: %d output fd: %d", input_fd, output_fd);
	close (input_fd);
	close (output_fd);
}

void	check_commands(char *argv[])
{
	if (access(argv[2], F_OK|X_OK) != 0)
	{
		ft_putstr_fd(argv[3], 2);
		ft_putstr_fd(": command not found\n", 2);
		//perror(argv[2]);
		exit (1);
	}
	if (access(argv[3], F_OK|X_OK) != 0)
	{
		ft_putstr_fd(argv[3], 2);
		ft_putstr_fd(": command not found\n", 2);
		// write(2, "\n", 1);
		// perror(argv[3]);
		exit (1);
	}
}
void	parse_input(int argc, char *argv[], char *envp[], t_args *arguments)
{
	if (argc != 5)
	{
		perror("Error: Wrong number of arguments");
		exit (1);
	}
	check_files(argv, arguments);
	search_path(envp, arguments);
	arguments->cmd1 = search_command(argv[2]);
	arguments->cmd2 = search_command(argv[3]);	
	//check_commands(argv);
}

int	main(int argc, char *argv[], char *envp[])
{
	
	t_args	arguments;

	parse_input(argc, argv, envp, &arguments);
	free_array(arguments.cmd1.cmd_str);
	free(arguments.cmd1.command);
	free_array(arguments.cmd1.flags);
	free_array(arguments.cmd2.cmd_str);
	free(arguments.cmd2.command);
	free_array(arguments.cmd2.flags);
	// while(*envp)
    //     printf("%s\n",*envp++);
	write(1, "Main program started\n", 21);
	return (0);
}