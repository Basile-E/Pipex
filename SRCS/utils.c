/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baecoliv <baecoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:23:27 by basile            #+#    #+#             */
/*   Updated: 2025/05/25 23:58:08 by baecoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	cleanup_error(int *fd, int filein, int fileout)
{
	perror("Error");
	// Close pipe file descriptors if provided
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	// Close input file if provided and valid
	if (filein > 0)
		close(filein);
	// Close output file if provided and valid
	if (fileout > 0)
		close(fileout);
	exit(EXIT_FAILURE);
}

void	empty_function(char **cmd)
{
	int	i;

	i = -1;
	ft_putstr_fd("Error: empty command\n", 2);
		if (cmd)
		{
			while (cmd[++i])
				free(cmd[i]);
			free(cmd);
		}
		exit(127);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	// Check if command is empty
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		empty_function(cmd);
	}
	path = find_path(cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		cleanup_error(NULL, -1, -1);
}

int	wait_for_processes(pid_t *pids)
{
	int	status1;
	int	status2;

	waitpid(pids[0], &status1, 0);
	waitpid(pids[1], &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	else if (WIFEXITED(status1))
		return (WEXITSTATUS(status1));
	return (1);
}
