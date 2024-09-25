/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/25 18:57:40 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"


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
	if (access(argv[2], X_OK) != 0)
	{
		ft_putstr_fd(argv[3], 2);
		ft_putstr_fd(": command not found\n", 2);
		//perror(argv[2]);
		exit (1);
	}
	if (access(argv[3], X_OK) != 0)
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
	while(*envp)
        printf("%s\n",*envp++);
	write(1, "Main program started\n", 21);
	return (0);
}