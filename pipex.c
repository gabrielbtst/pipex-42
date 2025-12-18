/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbatista <gbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:24:18 by gbatista          #+#    #+#             */
/*   Updated: 2025/11/11 20:40:01 by gbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	exec_cmd1(char *cmd, int infile_fd, int *pipe_fd, char **envp)
{
	char	**args;
	char	*path;

	dup2(infile_fd, 0);
	dup2(pipe_fd[1], 1);
	close(infile_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	args = ft_split(cmd, ' ');
	path = find_path(args[0], envp);
	execve(path, args, envp);
	perror("Error executing command");
	px_free_split(args);
	free(path);
	exit(EXIT_FAILURE);
}

void	exec_cmd2(char *cmd, int *pipe_read_fd, int outfile_fd, char **envp)
{
	char	**args;
	char	*path;

	dup2(outfile_fd, 1);
	dup2(pipe_read_fd[0], 0);
	close(outfile_fd);
	close(pipe_read_fd[0]);
	close(pipe_read_fd[1]);
	args = ft_split(cmd, ' ');
	path = find_path(args[0], envp);
	execve(path, args, envp);
	perror("Error executing command");
	px_free_split(args);
	free(path);
	exit(EXIT_FAILURE);
}

void	wait_children(void)
{
	wait(NULL);
	wait(NULL);
}

void	close_all(int *pipe_fd, int infile_fd, int outfile_fd)
{
	close(infile_fd);
	close(outfile_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (1);
	if (pipe(pipe_fd) == -1)
		perror("Error creating pipe");
	infile_fd = open_infile(argv[1]);
	outfile_fd = open_outfile(argv[4]);
	pid1 = execute_first(argv[2], infile_fd, pipe_fd, envp);
	pid2 = execute_second(argv[3], pipe_fd, outfile_fd, envp);
	wait_children();
	close_all(pipe_fd, infile_fd, outfile_fd);
	return (0);
}
