/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baecoliv <baecoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:34:31 by basile            #+#    #+#             */
/*   Updated: 2025/05/26 00:01:34 by baecoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		cleanup_error(fd, -1, -1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(filein);
	close(fd[0]);
	close(fd[1]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		cleanup_error(fd, -1, -1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	close(fd[0]);
	close(fd[1]);
	execute(argv[3], envp);
}

void	create_child_processes(char **argv, char **envp, int *fd, pid_t *pids)
{
	pids[0] = fork();
	if (pids[0] == -1)
		error();
	if (pids[0] == 0)
		child_process(argv, envp, fd);
	pids[1] = fork();
	if (pids[1] == -1)
		error();
	if (pids[1] == 0)
		parent_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
}

int	execute_pipeline(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pids[2];

	if (pipe(fd) == -1)
		error();
	create_child_processes(argv, envp, fd, pids);
	return (wait_for_processes(pids));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		return (execute_pipeline(argv, envp));
	else
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		return (1);
	}
}
//the new and last one