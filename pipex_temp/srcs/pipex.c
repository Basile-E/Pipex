/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basile <basile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:54:02 by basile            #+#    #+#             */
/*   Updated: 2025/05/23 01:46:58 by basile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

typedef struct s_pipex {
    int	    fd[2];
	pid_t	pid;
	char    *path;
	int     fd_in;
    int     fd_out;
    char    **exec_paths;
    char    *exec_temp;
    char    *full_path;
    char    **cmd;
    char    *key;
    char    *value;
    char    *result;
} t_pipex;


void free_array(char **array)
{
    int i;
    
    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
void    kill_all(t_pipex *pipex)
{
    if (!pipex)
        return;
    if (pipex->fd[0] > 0)
        close(pipex->fd[0]);
    if (pipex->fd[1] > 0)
        close(pipex->fd[1]);
    if (pipex->fd_in > 0)
        close(pipex->fd_in);
    if (pipex->fd_out > 0)
        close(pipex->fd_out);
    if (pipex->path)
        free(pipex->path);
    if (pipex->result)
        free(pipex->result);
    if (pipex->exec_paths)
        free_array(pipex->exec_paths);
    if (pipex->exec_temp)
        free(pipex->exec_temp);
    if (pipex->full_path)
        free(pipex->full_path);
    if (pipex->cmd)
        free_array(pipex->cmd);    
    free(pipex);
}

char *Find_Path(char **ep, t_pipex *pipex)
{
    int i;
    char **temp;
    
    i = 0;
    while(ep[i] != NULL)
    {
        temp = ft_split(ep[i], '=');
        pipex->key = temp[0];
        pipex->value = temp[1];
        if (ft_strncmp(pipex->key, "PATH", 4) == 0)
        {
            pipex->result = ft_strdup(pipex->value);
            free_array(temp);
            return (pipex->result);
        }
        free_array(temp);
        i++;
    }
    return (NULL);
}

// executeur, prend en param le path trouver par find path et le av[i] de la commande a executer
int execute(t_pipex *pipex, char *av, char **ep)
{
    int i;

    pipex->exec_paths = ft_split(pipex->path, ':');
    i = 0;
    while(pipex->exec_paths[i])
    {
        pipex->cmd = ft_split(av, ' ');
        pipex->exec_temp = ft_strjoin(pipex->exec_paths[i], "/");
        pipex->full_path = ft_strjoin(pipex->exec_temp, pipex->cmd[0]);
        free(pipex->exec_temp);
        if (access(pipex->full_path, F_OK) == 0)
        {
            execve(pipex->full_path, pipex->cmd, ep);
            free(pipex->full_path);
            free_array(pipex->cmd);
        }
        else
            i++;
        free(pipex->full_path);
        free_array(pipex->cmd);
    }
    free_array(pipex->exec_paths);
    return (0);
}

void    pipexx(t_pipex *pipex, char **ep, char **av)
{
    pipex->path = Find_Path(ep, pipex);	
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
        dup2(pipex->fd_in, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		execute(pipex, av[2], ep);
	}
	else if (pipex->pid > 0)
	{
        dup2(pipex->fd_out, STDOUT_FILENO);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[1]);
		execute(pipex, av[3], ep);
	}
}

int	main(int ac, char **av, char **ep)
{
    t_pipex *pipex;
    int status;
    
    pipex = malloc(sizeof(t_pipex));
	pipex->fd_in = open(av[1], O_RDONLY);
    pipex->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ac != 5)
    return (ft_printf("Error: Wrong number of arg\n"), kill_all(pipex), 0);
	if (pipe(pipex->fd) == -1)
    return (ft_printf("Error: Pipe creation failed\n"), kill_all(pipex), 0);
    pipexx(pipex, ep, av);
    waitpid(pipex->pid, &status, 0); 
    kill_all(pipex);
    return (0);
}
