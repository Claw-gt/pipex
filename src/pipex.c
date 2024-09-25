/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:02:03 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/25 12:28:51 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"


void	change_permissions(char *file)	
{
	char	*envp[] = {NULL};	
	char	*args[] = { "/usr/bin/chmod", "+rw", file, NULL };
	execve(args[0], args, envp);
    perror("Could not execve");
}

/*if open() fails, -1 is returned and errno is set to indicate the error.
When it creates outfile, it has no permissions at all*/
void	parse_input(int argc, char *argv[])
{
	if (argc != 5)
	{
		perror("Error: Wrong number of arguments");
		exit (1);
	}
	if (access(argv[1], R_OK) != 0)
	{
		//ft_putstr_fd(strerror(errno), 2);
		//write(2, "\n", 1);
		perror("infile");
		exit (1);
	}
	if (open("infile", O_RDONLY) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		perror("infile");
		exit (1);
	}
	if (open("outfile", O_CREAT|O_WRONLY|O_TRUNC) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		perror("outfile");
		exit (1);
	}
	if (access(argv[4], W_OK) != 0)
		change_permissions(argv[4]);
}

int	main(int argc, char *argv[])//, char *envp[])
{
	parse_input(argc, argv);
	write(1, "Main program started\n", 21);
	return (0);
}