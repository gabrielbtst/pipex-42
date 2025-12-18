/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbatista <gbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:03:47 by gbatista          #+#    #+#             */
/*   Updated: 2025/11/10 10:50:07 by gbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening infile");
		exit(1);
	}
	return (fd);
}

int	open_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error");
		exit(1);
	}
	return (fd);
}

char	*find_path(char *cmd, char **envp)
{
	size_t	i;
	char	*paths_string;
	char	*cmd_path;

	i = 0;
	if (envp[i] == NULL)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths_string = envp[i] + 5;
			cmd_path = search_in_paths(paths_string, cmd);
			return (cmd_path);
		}
		i++;
	}
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
{
	char	*cmd_path;
	char	*temp;

	temp = ft_strjoin(dir, "/");
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	return (cmd_path);
}

char	*search_in_paths(char *paths_string, char *cmd)
{
	char	**paths;
	char	*cmd_path;
	size_t	j;

	j = 0;
	paths = ft_split(paths_string, ':');
	while (paths[j])
	{
		cmd_path = join_path(paths[j], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			px_free_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
		j++;
	}
	px_free_split(paths);
	return (NULL);
}
