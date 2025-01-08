/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:43:08 by qais              #+#    #+#             */
/*   Updated: 2025/01/08 14:30:37 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int fd)
{
	perror("\033[0;31mERROR\033[0m");
	if (fd > 0)
		close (fd);
	exit(EXIT_FAILURE);
}

void	ft_free_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	exit_pipe(t_data *data)
{
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
	perror("Skill issue\n");
	exit(EXIT_FAILURE);
}
