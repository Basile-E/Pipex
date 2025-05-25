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

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
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
		error();
}

void check_file_size(char *filename)
{
    int fd;
    char buffer[4096];
    ssize_t bytes_read;
    size_t total_size = 0;
    const size_t size_limit = 104857600;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return;
        
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        total_size += bytes_read;
        if (total_size > size_limit)
        {
            close(fd);
            ft_putstr_fd("\033[31mError: Input file too large\n\e[0m", 2);
            exit(1);
        }
    }
    
    close(fd);
}
