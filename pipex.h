/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:29:41 by qhatahet          #+#    #+#             */
/*   Updated: 2025/01/08 14:04:10 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H 

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	pid_t	id1;
	pid_t	id2;
	int		fd[2];
}		t_data;

typedef struct s_helpers
{
	char	**paths;
	char	*joined;
	char	*temp;
	int		i;
}		t_helpers;

char	*get_path(char *cmd, char **envp);
void	ft_execute(int fd, char *cmd, char **envp);
void	ft_exit(int fd);
void	ft_free_2d(char **s);
int		get_cmd(char **cmd, t_helpers *helper, char **envp);

#endif
