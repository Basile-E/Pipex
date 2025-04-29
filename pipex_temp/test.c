#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Libft/libft.h"


// find path prend en param la variable d'env et renvoi une string contenant tout les PATH separer par ':'
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
int execute(char *path, char **av, char **ep)
{
    int i;
    char **exec_paths = ft_split(path, ':');
    i = 0;
    ft_printf("valeur de i %i\n", i);
    while(exec_paths[i] != NULL)
    {
        char **cmd = ft_split(av[1], ' '); // separe la commande de ses params
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
}
int main(int ac, char **av, char **ep)
{

    char *path = Find_Path(ep);
    
    
    execute(path, av, ep);
    
}
