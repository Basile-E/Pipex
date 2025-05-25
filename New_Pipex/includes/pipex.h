#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../Libft/libft.h"

void    error(void);
char    *find_path(char *cmd, char **envp);
void    execute(char *argv, char **envp);
void    check_file_size(char *filename);

#endif