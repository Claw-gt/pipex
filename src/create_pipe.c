/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:08:46 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/09 15:37:53 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	parent(int *pipe_fd, int *pid)
{
	pid_t	wait_pid[2];
	int		status[2];

	close(pipe_fd[READ_END]);
	wait_pid[0] = waitpid(pid[0], &status[0], 0);
	//printf("Status: %d\n", WEXITSTATUS(status[0]));
	wait_pid[1] = waitpid(pid[1], &status[1], 0);
	//printf("Status: %d\n", WEXITSTATUS(status[1]));
	if (wait_pid[0] == -1 || wait_pid[1] == -1)
		print_errno("Wait failed");
	// else if (WEXITSTATUS(status[0]) != EXIT_SUCCESS ||
	// 		WEXITSTATUS(status[1]) != EXIT_SUCCESS)
	// 	custom_error("Error: Child process failed");
}

void	child1(t_args arguments, int *pipe_fd, char **envp)
{
	close(pipe_fd[READ_END]);
	if (dup2(arguments.input_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(arguments.input_file);
	close(pipe_fd[WRITE_END]);
	execute_cmd(envp, arguments.cmd1);
}

void	child2(t_args arguments, int *pipe_fd, char **envp)
{
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(arguments.output_file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	// ya tenemos dos fds que apuntan a lo mismo. Cerramos uno
	close(pipe_fd[READ_END]);
	close(arguments.output_file);
	execute_cmd(envp, arguments.cmd2);
}

void	create_pipe(t_args arguments, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
		print_errno("Pipe failed");
	pid[0] = fork();
	if (pid[0] == -1)
		print_errno("Fork failed");
	else if (pid[0] == 0)
		child1(arguments, pipe_fd, envp);
	else
	{
		close(pipe_fd[WRITE_END]);
		pid[1] = fork();
		if (pid[1] == -1)
			print_errno("Fork failed");
		else if (pid[1] == 0)
			child2(arguments, pipe_fd, envp);
		else
			parent(pipe_fd, pid);
	}
}
