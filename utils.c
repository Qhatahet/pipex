/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:37:08 by qais              #+#    #+#             */
/*   Updated: 2025/01/07 15:51:36 by qais             ###   ########.fr       */
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

char	*get_path(char *cmd, char **envp, t_helpers helper)
{
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
	return (helper.joined);
}

void	ft_execute(int fd, char *cmd, char **envp)
{
	char		**vector;
	t_helpers	helper;

	vector = ft_split(cmd, ' ');
	if (!vector)
		ft_exit(fd);
	cmd = get_path (vector[0], envp, helper);
	execve(cmd, vector, envp);
}
