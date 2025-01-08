/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhatahet <qhatahet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:37:08 by qais              #+#    #+#             */
/*   Updated: 2025/01/08 19:59:37 by qhatahet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmd(char **cmd, t_helpers *helper, char **envp)
{
	*cmd = ft_strjoin("/", *cmd);
	if (!cmd)
		return (0);
	helper->paths = NULL;
	helper->i = 0;
	while (envp[helper->i])
	{
		if (ft_strncmp(envp[helper->i], "PATH=", 5) == 0)
		{
			helper->paths = ft_split(envp[helper->i] + 5, ':');
			if (!helper->paths)
				return (0);
			return (1);
		}
		helper->i++;
	}
	return (0);
}

char	*get_path(char *cmd, char **envp)
{
	t_helpers	helper;

	helper.paths = NULL;
	helper.joined = NULL;
	if (!get_cmd(&cmd, &helper, envp))
		return (NULL);
	helper.i = 0;
	while (helper.paths[helper.i])
	{
		helper.temp = ft_strjoin(helper.paths[helper.i], cmd);
		if (!helper.temp)
			return (NULL);
		if (!access(helper.temp, X_OK))
		{
			helper.joined = helper.temp;
			break ;
		}
		free (helper.temp);
		helper.i++;
	}
	free(cmd);
	ft_free_2d(helper.paths);
	return (helper.joined);
}

void	ft_execute(int fd, char *cmd, char **envp)
{
	char		**vector;

	vector = ft_split(cmd, ' ');
	if (!vector)
		ft_exit(fd);
	if (*cmd == 0 || *cmd == ' ')
	{
		ft_free_2d(vector);
		ft_exit(fd);
	}
	if (cmd[0] == '/')
	{
		if (!access(cmd, X_OK))
			execve(cmd, vector, envp);
		ft_free_2d(vector);
		return ;
	}
	cmd = get_path (vector[0], envp);
	execve(cmd, vector, envp);
}
