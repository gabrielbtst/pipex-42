/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbatista <gbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:44:46 by gbatista          #+#    #+#             */
/*   Updated: 2025/11/11 21:22:27 by gbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

pid_t	execute_first(char *cmd, int infile_fd, int *pipe_fd, char **envp)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
		perror("Error");
	if (pid1 == 0)
		exec_cmd1(cmd, infile_fd, pipe_fd, envp);
	close(infile_fd);
	close(pipe_fd[1]);
	return (pid1);
}

pid_t	execute_second(char *cmd, int *pipe_read, int outfile_fd, char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		perror("Error");
	if (pid2 == 0)
		exec_cmd2(cmd, pipe_read, outfile_fd, envp);
	close(outfile_fd);
	close(pipe_read[0]);
	return (pid2);
}

void	px_free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
