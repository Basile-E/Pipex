/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basile <basile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:34:31 by basile            #+#    #+#             */
/*   Updated: 2025/05/25 16:38:51 by basile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;
	
	check_file_size(argv[1]);

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
    int		fd[2];
    pid_t	pid1;
    pid_t   pid2;
    int     status1, status2;

    if (argc == 5)
    {
        if (pipe(fd) == -1)
            error();
        pid1 = fork();
        if (pid1 == -1)
            error();
        if (pid1 == 0)
            child_process(argv, envp, fd); 
		close(fd[1]);
        

        pid2 = fork();
        if (pid2 == -1)
            error();
        if (pid2 == 0)
            parent_process(argv, envp, fd);
        close(fd[0]);
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);
        if (WIFEXITED(status2))
            return (WEXITSTATUS(status2));
        else if (WIFEXITED(status1))
            return (WEXITSTATUS(status1));
        return (1);
    }
    else
    {
        ft_putstr_fd("Error: Bad arguments\n", 2);
        ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
        return (1);
    }
}
