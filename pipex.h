/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbatista <gbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:03:32 by gbatista          #+#    #+#             */
/*   Updated: 2025/11/11 20:41:45 by gbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	exec_cmd1(char *cmd, int infile_fd, int *pipe_fd, char **envp);
void	exec_cmd2(char *cmd, int *pipe_fd, int outfile_fd, char **envp);
pid_t	execute_first(char *cmd, int infile_fd, int *pipe_fd, char **envp);
pid_t	execute_second(char *cmd, int *pipe_fd, int outfile_fd, char **envp);
void	wait_children(void);
int		open_outfile(char *filename);
int		open_infile(char *filename);
void	close_all(int *pipe_fd, int infile_fd, int outfile_fd);
char	*join_path(char *dir, char *cmd);
char	*find_path(char *cmd, char **envp);
char	*search_in_paths(char *paths_string, char *cmd);
void	px_free_split(char **split);

#endif
