/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:20:20 by clagarci          #+#    #+#             */
/*   Updated: 2024/09/24 13:45:19 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipex(int argc, char *argv[])
{
	int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Child reads from pipe */
        close(pipefd[1]);          /* Close unused write end */
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {            /* Parent writes argv[1] to pipe */
        close(pipefd[0]);          /* Close unused read end */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Reader will see EOF */
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argv;
    (void) envp;
	if (argc < 1)
		return (1);
	//printf("Error %s", strerror(ft_atoi(argv[1])));
    printf("Main program started\n");
    char* args[] = { "/usr/ls", "-la", "../so_long/", NULL };
    if (access(args[0], X_OK) != 0)
        write(1, "Error", 5);
    execve(args[0], args, envp);
    perror("Could not execve");
    write(1, "hello", 5);
    //return 1;
	//pipex(argc, argv);
	return (0);
}