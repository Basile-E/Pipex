/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basile <basile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:54:02 by basile            #+#    #+#             */
/*   Updated: 2025/04/29 17:10:29 by basile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


char *Find_Path(char **ep)
{
    int i = 0;
    char *env_variable = ep[i];
    char *key;
    char *value;
        
    while(env_variable != NULL)
    {

        char **temp = ft_split(env_variable, '=');
        key = temp[0];
        value = temp[1];
        if (ft_strncmp(key, "PATH", 4) == 0)
        {
            //ft_printf("key = %s\n\n", key);
            //ft_printf("value = %s\n\n", value);
            //ft_printf("PATH value is %s\n\n", value);
            break;
        }
        env_variable = ep[i];
        i++;
    }
    //ft_printf("valeur de i %i\n", i);
    return (value);
}

// executeur, prend en param le path trouver par find path et le av[i] de la commande a executer
int execute(char *path, char *av, char **ep)
{
    int i;
    char **exec_paths = ft_split(path, ':');
    i = 0;
    //ft_printf("valeur de i %i\n", i);
    while(exec_paths[i] != NULL)
    {
        char **cmd = ft_split(av, ' '); // separe la commande de ses params
        char *exec_temp = ft_strjoin(exec_paths[i], "/"); // prend le exec_path qu'on tente et lui ajoute '/'
        exec_temp = ft_strjoin(exec_temp, cmd[0]); // et ajoute la commande au bout du path pour voir si le fichier existe
        //ft_printf("exec_temp = %s\n", exec_temp);
        if (access(exec_temp, F_OK) == 0) // veriffie que le programme existe ou non
        {
            //ft_printf("Executalble trouver = %s\n\n", exec_temp);
            execve(exec_temp, cmd, ep);
        }
        else
            i++;
    }
	return (0);
}

int	main(int ac, char **av, char **ep)
{
	int	fd[2];
	pid_t	pid;
	char *path;
	int fd_in = open(av[1], O_RDONLY);
    int fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if (ac != 5)
		return (ft_printf("Error: Wrong number of arg\n"));
	if (pipe(fd) == -1)
		return (ft_printf("Error: Pipe creation failed\n"));
    // si le program est trop long je peux faire une fonction pipex avec un copier coler de ce qu'il y a en dessous
	path = Find_Path(ep);	
	pid = fork();
	if (pid == 0)
	{
        dup2(fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execute(path, av[2], ep);
	}
	else if (pid > 0)
	{
        dup2(fd_out, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execute(path, av[3], ep);
	}
    return (0);
}
