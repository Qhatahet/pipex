/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:43:08 by qais              #+#    #+#             */
/*   Updated: 2025/01/09 16:50:58 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int fd)
{
	if (errno != 0)
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

void	ft_invalid_args(int argc)
{
	if (argc > 5)
		ft_putstr_fd("\033[0;31mERROR\033[0m: too many arguments\n", 2);
	else if (argc < 5)
		ft_putstr_fd("\033[0;31mERROR\033[0m: too few arguments\n", 2);
	ft_putstr_fd("./pipex file1 cmd1 cmd2 file2", 2);
	exit(EXIT_FAILURE);
}
