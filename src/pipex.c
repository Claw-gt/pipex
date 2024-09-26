/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/26 15:59:56 by clagarci         ###   ########.fr       */
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

void	search_command(char *envp[])
{
	char	*path_env;
	char	**path_array;

	while(*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_env = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
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
		envp++;		
	}
	ft_printf("path: %s\n", path_array[0]);
	free_array(path_array);
}
void	change_permissions(char *file)	
{
	char	*envp[1];
	char	*args[4];
	
	args[0] = "/usr/bin/chmod";
	args[1] = "+rw";
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
	check_commands(argv);
}

int	main(int argc, char *argv[], char *envp[])
{
	parse_input(argc, argv);
	search_command(envp);
	// while(*envp)
    //     printf("%s\n",*envp++);
	write(1, "Main program started\n", 21);
	return (0);
}