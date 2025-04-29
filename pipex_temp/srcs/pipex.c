/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basile <basile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 09:54:02 by gcollet           #+#    #+#             */
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
            ft_printf("key = %s\n\n", key);
            ft_printf("value = %s\n\n", value);
            ft_printf("PATH value is %s\n\n", value);
            break;
        }
        env_variable = ep[i];
        i++;
    }
    ft_printf("valeur de i %i\n", i);
    return (value);
}

// executeur, prend en param le path trouver par find path et le av[i] de la commande a executer
int execute(char *path, char *av, char **ep)
{
    int i;
    char **exec_paths = ft_split(path, ':');
    i = 0;
    ft_printf("valeur de i %i\n", i);
    while(exec_paths[i] != NULL)
    {
        char **cmd = ft_split(av, ' '); // separe la commande de ses params
        char *exec_temp = ft_strjoin(exec_paths[i], "/"); // prend le exec_path qu'on tente et lui ajoute '/'
        exec_temp = ft_strjoin(exec_temp, cmd[0]); // et ajoute la commande au bout du path pour voir si le fichier existe
        ft_printf("exec_temp = %s\n", exec_temp);
        if (access(exec_temp, F_OK) == 0) // veriffie que le programme existe ou non
        {
            ft_printf("Executalble trouver = %s\n\n", exec_temp);
            execve(exec_temp, cmd, ep); // execute le program trouver 
        }
        else
            ft_printf("Exec non trouver on continue, i = %i\n", i++);
    }
	return (0);
}


int	main(int ac, char **av, char **ep)
{
	int	fd[2];
	int	pid;
	char *path;

	// int fd_in = open(readonly)
	// int fd_out = open(writeonly, create)
	
	if (ac != 5)
		return (ft_printf("Error: Wrong number of arg\n"));
	if (pipe(fd) == -1)
		return (ft_printf("Error: Pipe creation failed\n"));
		//👮‍♂️ verification des arguments passez votre chemin 👮‍♂️
	
	path = Find_Path(ep);
		
	// il faut que :
	// le process enfant ouvre le fichier1 et execute ls dessus (comment ?)
	// puis redirige la sortie de ls (ls std output ?) ver pipe[1] (l'ecriture dans la pipe)
	
	// le processus parent ouvre ou crée le fichier2 et execute wc dessus (idem comment ?)
	// puis redirige la sorti

	
	pid = fork();
	if (pid == 0)
	{
		ft_printf("welcom from the child process\n");
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_printf("av[2] = %s\n", av[2]);
		execute(path, av[2], ep);
	}
	else if (pid > 0)
	{
		//gwait(NULL);
		ft_printf("welcom from the parrent process\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execute(path, av[3], ep);
	}	
}
