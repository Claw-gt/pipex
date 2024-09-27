/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/27 13:44:20 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

char	**search_path(char *envp[])
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
	return (path_array);
}

void	search_command(char *argv[])
{
	t_cmd	cmd1;
	t_cmd	cmd2;

	cmd1.cmd_str = ft_split(argv[2], ' ');
	cmd1.command = cmd1.cmd_str[0];
	cmd2.cmd_str = ft_split(argv[3], ' ');
	cmd2.command = cmd2.cmd_str[0];
	if (!cmd1.cmd_str || !cmd2.cmd_str)
		exit(1);
	ft_printf("arg: %s COMMAND 1: %s\n", argv[2], cmd1.command);
	ft_printf("arg: %s COMMAND 2: %s", argv[3], cmd2.command);	
	free_array(cmd1.cmd_str);
	free_array(cmd2.cmd_str);
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
void	check_files(char *argv[])
{
	if (access(argv[1], F_OK) == 0)
	{
		if (open("infile", O_RDONLY) == -1)
		{
			// ft_putstr_fd(strerror(errno), 2);
			// write(2, "\n", 1);
			perror("infile");
			exit (1);
		}
	}
	else
	{
		// ft_putstr_fd(strerror(errno), 2);
		// write(2, "\n", 1);
		perror("infile");
		exit (1);
	}
	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], R_OK|W_OK) != 0)
			change_permissions(argv[4]);
	}
	else
	{
		if (open("outfile", O_CREAT|O_WRONLY|O_TRUNC) == -1)
		{
			// ft_putstr_fd(strerror(errno), 2);
			// write(2, "\n", 1);
			perror("outfile");
			exit (1);
		}
	}
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
void	parse_input(int argc, char *argv[])
{
	if (argc != 5)
	{
		perror("Error: Wrong number of arguments");
		exit (1);
	}
	check_files(argv);
	//check_commands(argv);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**path;

	parse_input(argc, argv);
	search_command(argv);
	path = search_path(envp);
	free_array(path);
	// while(*envp)
    //     printf("%s\n",*envp++);
	write(1, "Main program started\n", 21);
	return (0);
}