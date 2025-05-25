/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baecoliv <baecoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:23:30 by basile            #+#    #+#             */
/*   Updated: 2025/05/25 23:58:23 by baecoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	cleanup_error(int *fd, int filein, int fileout);
int	    wait_for_processes(pid_t *pids);

#endif