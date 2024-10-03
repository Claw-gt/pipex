/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:48:46 by clagarci          #+#    #+#             */
/*   Updated: 2024/10/03 13:10:49 by clagarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	command_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	create_pipe(t_args arguments, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid[2];
	pid_t	wait_pid[2];
	int		status[2];

	if (pipe(pipe_fd) == -1)
		print_errno("Pipe failed");
	pid[0] = fork();
	printf("pid[0]: %d\n", pid[0]);
	if (pid[0] == -1)
		print_errno("Fork failed");
	else if (pid[0] == 0)
	{
		close(pipe_fd[READ_END]);
		if (dup2(arguments.input_file, STDIN_FILENO) == -1)
			print_errno("dup2 (infile) failed");
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
			print_errno("dup2 (write end) failed");
		close(arguments.input_file);
		close(pipe_fd[WRITE_END]);
		execute_cmd(envp, arguments.cmd1);
	}
	else
	{
		close(pipe_fd[WRITE_END]);
		pid[1] = fork();
		if (pid[1] == -1)
			print_errno("Fork failed");
		else if (pid[1] == 0)
		{
			if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
				print_errno("dup2 (read end) failed");
			if (dup2(arguments.output_file, STDOUT_FILENO) == -1)
				print_errno("dup2 (outfile) failed");
			close(pipe_fd[READ_END]); // ya tenemos dos fds que apuntan a lo mismo. Cerramos uno
			close(arguments.output_file);
			execute_cmd(envp, arguments.cmd2);
		}
		else
		{
			close(pipe_fd[READ_END]);
			wait_pid[0] = waitpid(pid[0], &status[0], 0);
			printf("WAit pid %d Status: %d", wait_pid[0], WEXITSTATUS(status[0]));
			wait_pid[1] = waitpid(pid[1], &status[1], 0);
			printf("Status: %d", WEXITSTATUS(status[1]));
			if (wait_pid[0] == -1 || wait_pid[1] == -1)
				print_errno("Wait failed");
			else if (WEXITSTATUS(status[0]) != EXIT_SUCCESS || WEXITSTATUS(status[1]) != EXIT_SUCCESS)
				custom_error("Error: Child process failed");
		}
	}
}

void	execute_cmd(char **envp, t_cmd cmd)
{
	char	**argv;
	int		i;

	i = 1;
	argv = ft_calloc(command_len(cmd.cmd_str) + 1, sizeof(char *));
	if (!argv)
		custom_error("Error: Could not allocate memory");
	argv[0] = cmd.command;
	while (cmd.cmd_str[i])
	{
		argv[i] = cmd.cmd_str[i];
		i++;
	}
	argv[i] = NULL;
	execve(argv[0], argv, envp);
	print_errno("Execve failed");
}
